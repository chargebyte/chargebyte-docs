.. _carrierboard_development.rst:

********************************
Custom Carrier Board Development
********************************

After the evaluation of the Charge SOM platform based on chargebyte's Evaluation Board (EVB), the customer
might have the wish to create a customer-specific carrier board that best fits their individual requirements.

During hardware development, customers are advised to not only pay attention to the hardware requirements
like choosing connectors, board layout etc. but also have software engineering in mind, product life cycle,
product variants and similar aspects.

At chargebyte, the Charge SOMs are not only manufactured for each customer request but we aim to have
some boards in stock to fulfill customer request demands in a timely fashion. This means that we pre-install
a firmware on the boards which has a given software revision and may include only software support for
carrier boards which are already know at the time of manufacturing. However, this has the small disadvantage that
customers could mount the Charge SOM on carrier boards without prior updating the factory firmware. In this
case, there might be a minimal electrical risk that the software configuration of the board connector does not
match the electrical expectation/requirement of the carrier board.
To prevent this and to have a more Plug & Play like feeling, customers can place an EEPROM on their custom
carrier board design. The idea is not new: similiar to the well-known Raspberry Pi(tm) ecosystem where
Pi HATs also use such an EEPROM, the U-Boot bootloader of the Charge SOM checks such an EEPROM - when available - for
a Device Tree overlay which is then loaded and passed to the Linux kernel dynamically. This allows customers
to model all the specific pin settings of their custom carrier board so that the electrical compatibitiliy
is ensured.

Such an EEPROM has to be connected to the ``I2C1`` pins ``SCL`` (Connector X5/41) and ``SDA`` (Connector X5/43) and
it must be configured for I2C address ``0x50``.
chargebyte recommends to plan with an EERPOM of at least 32 kB (kilobyte), i.e. a 24C256 [#]_: the Device Tree
overlay and a digital signature must fit into it.
Once the customer has created the Device Tree overlay and signature and it also fits into
e.g. a 16 kB EEPROM, it is usually only a BOM change to populate such a smaller version.

.. [#] Many vendors provide compatible devices. In Device Tree, we still recommend to use
       ``compatible = "atmel,24c256"`` since U-Boot does not support other vendor prefixes than ``atmel``.

The EEPROM content consists of a 128 byte fixed-length header and a variable length DT overlay content,
plus a variable length digital signature (optional for now) for the DT overlay blob.

The C structure for the header looks like follows:

.. code-block:: c

   struct cb_dt_eeprom_header {
       uint16_t signature;                  /* big-endian 'CB' = 0x4342 */
       uint8_t  reserved0;                  /* 0x00 */
       uint8_t  header_version;             /* 0x01 */
       uint16_t dt_offset;                  /* little-endian */
       uint16_t dt_size;                    /* little-endian */
       uint16_t dt_sig_offset;              /* little-endian */
       uint16_t dt_sig_size;                /* little-endian */
       uint32_t vendor_code;                /* little-endian */
       union {
           struct {
               uint32_t hw_rev;             /* special encoding, see below */
               uint8_t  order_code[32];     /* ASCII string */
               uint8_t  reserved1[72];
           } cb_dt_chargebyte;
       } vendor_specific;
       uint32_t crc32;                      /* little-endian */
   };

Or, presented in a more visually appealing ASCII art way:

::

   +--------++-----+-----+-----+-----+-----+-----+-----+-----+-------+-------+-------+-------+-----+-----+-----+-----+
   | Offset || 0x0 | 0x1 | 0x2 | 0x3 | 0x4 | 0x5 | 0x6 | 0x7 |  0x8  |  0x9  |  0xA  |  0xB  | 0xC | 0xD | 0xE | 0xF |
   +========++=====+=====+=====+=====+=====+=====+=====+=====+=======+=======+=======+=======+=====+=====+=====+=====+
   | 0x0000 || 'C' | 'B' | 0x0 | 0x1 | DT Offset |  DT Size  | DT Signature  | DT Signature  |      Vendor Code      |
   |        ||     |     |     |     |           |           |    Offset     |     Size      |                       |
   +--------++-----+-----+-----+-----+-----+-----+-----+-----+-------+-------+-------+-------+-----+-----+-----+-----+
   | 0x0010 ||                                       Vendor Specific                                                 |
   +--------++-------------------------------------------------------------------------------------------------------+
   |  ...   ||                                   Vendor Specific (cont.)                                             |
   +--------++-------------------------------------------------------------------------------+-----------------------+
   | 0x0070 ||                           Vendor Specific (cont.)                             |         CRC32         |
   +--------++-------------------------------------------------------------------------------+-----------------------+
   | 0x0080 ||                                       Device Tree Overlay BLOB                                        |
   +--------++-------------------------------------------------------------------------------------------------------+
   |  ...   ||                                    Device Tree Overlay BLOB (cont.)                                   |
   +--------++-------------------------------------------------------------------------------------------------------+
   |  ...   ||                                  Device Tree Overlay Signature BLOB                                   |
   +--------++-------------------------------------------------------------------------------------------------------+
   |  ...   ||                             Device Tree Overlay Signature BLOB (cont.)                                |
   +--------++-------------------------------------------------------------------------------------------------------+

Additional notes regarding the content:

- All multi-byte fields use the little-endian byte order since U-Boot and Linux kernel run the CPU in little-endian
  mode and thus it is simpler to use the fields. Only the leading signature is stored big-endian to have a
  human-friendly nice hexdump when looking at the EEPROM content.
- The ``DT offset`` can point to any location in the EEPROM. It is not required that the DT Overlay Blob starts directly
  after the header. This allows for vendors to store custom data and/or additional fields in the EEPROM.
- The same applies to the DT Overlay Signature Blob.
- The vendor specific header part can also be used for customer specific data. The C structure reflects what chargebyte
  is going to use as an example.
- The ``Vendor Code`` can be used by customers to identify different carrier boards and/or to determine how the vendor
  specific area is structured. chargebyte will use the fixed-value 0x63624342 (ASCII “cbCB” → 0x42 0x43 0x62 0x63 in
  little-endianess) for its boards. Customers can choose arbitrary values ​​here, but it is recommended (though not
  mandatory) to coordinate the value with chargebyte. If desired, chargebyte can also record such values here in this
  documentation.
- As example, chargebyte will use the vendor specific part to store a hardware board revision and an order code
  of this board model. It can be accessed in the field later by the firmware for debugging and/or maintainance purpose.
  Customers might have their own requirements to store individual board specific, or general product information.
- The header check in U-Boot will be very simple for the moment: only the CRC32 is validated and when it is correct,
  then DT offset and DT length fields are used without further checks.
  Customers are advised to fully comply with this specification since the implemented behaviour can be extended
  to be more strict in the future.
- The digital DT overlay signature is currently not checked by U-Boot or any other software component but this
  is recommended for production use. chargebyte aims to extend the software support for this later.

The idea of the digital DT overlay signature is to ensure that the Device Tree overlay blob is from a trusted source and
thus can be loaded and used without damaging the system. The signature can be created using a X.509 certificate
using e.g. ``openssl cms …`` and thus creating a *detached* signature of the binary DT overlay file.

To keep the DT overlay signature small, the certificate could be *not* included in this signature (and thus not stored
inside the EEPROM), but to verify this signature, accessing the signing certificate must then be possible
(e.g. placed in and loaded from the root filesystem). This raises other topics, so chargebyte's start point is
to include it as a complete X.509 signature in the EEPROM even if this requires a larger EEPROM type.

Such a signature can be created for example using the following command line:

.. code-block:: shell

   openssl cms -sign -in imx93-charge-som-my-custom-carrier-board.dtbo -out imx93-charge-som-my-custom-carrier-board.dtbo.sig -outform DER -binary -signer my-company.crt -inkey my-company.key

It is possible to re-use an existing Public-Key Infrastructure which is already used for signing the firmware
update files.

Once a matching Device Tree overlay and the corresponding signature are available, the EEPROM content needs
to be created using the helper tool ``cb-dt-eeprom`` which is included in chargebyte's Github space:
https://github.com/chargebyte/cb-eeprom-utils

An example invocation for the carrier board used as the base for chargebyte's Charge Control V is shown below.
It uses the typical chargebyte board revision number and an order code assigned to this carrier board type.

.. code-block:: shell

   cb-dt-eeprom -r V0R1a -o CBCSOMC-D200-00001 imx93-charge-control-v.dtbo imx93-charge-control-v.dtbo.sig > dt-eeprom.bin

For a random customer, this might look like this (here with a randomly chosen vendor code):

.. code-block:: shell

   cb-dt-eeprom --vendor-code 0x6d686569 imx93-charge-som-my-custom-carrier-board.dtbo imx93-charge-som-my-custom-carrier-board.dtbo.sig > dt-eeprom.bin

During carrier board manufacturing, it is assumed that writing the EEPROM is done via an external programmer
which is out-of-scope for this documentation.

But during the development phase, it might be necessary to exchange the EEPROM content and/or rewrite it for
testing purpose. Then using an external programmer is cumbersome. Better and simpler is to write the
created binary EEPROM image file into the EEPROM directly from the Charge SOM hooked up to such a carrier
board. The following command can be used via SSH and/or Debug UART:

.. code-block:: shell

   dd if="dt-eeprom.bin" of=/sys/class/i2c-dev/i2c-0/device/0-0050/eeprom

Even so, it's still a complex process and long round trip. So it is possible to directly place such Device Tree overlay
files in the root filesystem of the firmware in the ``/boot`` directory.
Loading of such files can be controlled with the U-Boot environment variable ``overlays``. This variable can
hold a whitespace separated list of filenames (basename of the file, i.e. without ``/boot`` prefix) which are
loaded and merged in order *after* the base Device Tree file (given via ``fdtfile`` environment variable) is loaded.
This approach can also be used for a custom carrier board when the EEPROM approach does not fit.

Here is a summary of related U-Boot environment variables:

+------------------------------+------------------------------------------------------------------------------+
| U-Boot Variable Name         | Description                                                                  |
+==============================+==============================================================================+
| fdtfile                      | The base Device Tree blob to load. This variable must be always set          |
|                              | to a valid filename of a file in ``/boot``.                                  |
|                              | By default, this variable is set to ``imx93-charge-som.dtb``.                |
+------------------------------+------------------------------------------------------------------------------+
| overlays                     | List of filenames to be loaded as DT overlays.                               |
|                              | Unset by default.                                                            |
+------------------------------+------------------------------------------------------------------------------+
| no_overlays                  | Boolean flag, i.e. ``0`` or ``1``. Can be used to disable the DT             |
|                              | overlay loading from filesystem completely. Set to ``0`` by default.         |
+------------------------------+------------------------------------------------------------------------------+
| no_eeprom_dtbo               | Boolean flag, i.e. ``0`` or ``1``. Can be used to disable the DT             |
|                              | overlay loading from EEPROM. Set to ``0`` by default.                        |
|                              | Can - for example - be used during DT oveerlay development.                  |
+------------------------------+------------------------------------------------------------------------------+

From Linux user-space, such U-Boot environment variables can be displayed with ``fw_printenv`` and set
with ``fw_setenv`` utility. Both tools are included in chargebyte's example firmware image.
