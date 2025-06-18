***********
Development
***********

This chapter shows which options are available to customize the charge controller to your own needs. It
starts with creating your own EVerest modules that can be cross-compiled and run on the target, up to
creating fully customized firmware images that can be installed on the target. This chapter also
explains how to debug issues within the EVerest environment on the target.

Checklist before starting
=========================

The following bullet points should be checked before starting with the development of a custom EVerest
module:

* Please make sure that your charge controller is started and running (see :ref:`getting_started.rst` chapter).
  It is recommended to connect the charge controller to the local computer via Ethernet. This makes it
  easier to share files (e.g. configuration, image, binary, or logging files) between the local computer
  and the charge controller.

* The EVerest development environment should be set up on the local Linux machine. Please follow the
  instructions in the EVerest documentation, in particular the chapter `Prepare Your Development Environment <https://everest.github.io/nightly/general/02_detail_pre_setup.html>`_
  and the chapter `A Kind Of Quick Guide To EVerest <https://everest.github.io/nightly/general/03_quick_start_guide.html>`_.
  If you have problems setting up EVerest, please check the `Zulip chat <https://lfenergy.zulipchat.com/>`_
  to see whether this problem is already known and whether solutions have already been found.
  To verify that everything is installed correctly, EVerest should be compiled once natively on your
  system.

* Keep in mind that if you want to cross-compile an EVerest module, it must be compatible with the EVerest
  release used in the firmware. Please have a look at the official `EVerest documentation <https://everest.github.io/nightly/dev_tools/edm.html#setting-up-and-updating-a-workspace>`_
  to learn how to check out a dedicated EVerest release. The everest-core version used by the firmware
  can be found in the release notes of the `firmware image <https://github.com/chargebyte/meta-chargebyte-everest/releases>`_.

Best practices for developing EVerest modules
=============================================

It is recommended to develop your custom software on your local PC Linux environment, using a compiler,
debugger, and tools that you are familiar with. Using tools like autotools, cmake, and pkg-config
in your own projects makes the integration and cross-compiling process much easier.

A native installation of EVerest on your host system is also recommended, as it includes simulation examples
that allow you to start and test EVerest locally on your machine. If the software you developed does
not depend on specific hardware components, it is also possible to test your EVerest module natively
on the local machine before it is executed on the target hardware platform.
Please refer to `Simulating EVerest <https://everest.github.io/nightly/tutorials/run_sil/index.html>`_ for more information
on how to start your EVerest module in the SiL environment.

If you are starting your program from scratch and considering additional libraries to support specific
functionality, first review the libraries already required by EVerest or included in the firmware’s Linux
distribution. Minimizing dependencies helps reduce the size of the firmware update image, resulting in
faster transfer and flashing times during board updates.

When developing your software component, you need to decide how it will interact with the EVerest stack.
You can either implement your software as an EVerest module and use the internal interfaces to communicate
with the stack, or you can use the external MQTT-based EVerest API `API <https://github.com/EVerest/everest-core/tree/main/modules/API>`_
provided by the API module to access the EVerest stack. For energy management use cases, the second option
is certainly a valid approach. However, the standard and more flexible path is to create a dedicated EVerest
module. For energy management use cases, a websocket JSON-RPC-based approach to communicate with the
EVerest stack will be available in the near future. For more information, feel free to contact us.

The process of creating your own EVerest modules is described in the EVerest documentation:
`How to: Develop New Modules <https://everest.github.io/nightly/tutorials/new_modules/index.html>`_.

.. note::
   It is also possible to create your module directly in the everest-core project in the modules directory. 
   This is only recommended if you either want to work on a fork of everest-core or if you want to
   contribute the module to the EVerest core project. In general, it is recommended to create your own module
   in a separate EVerest module repository as described in the EVerest documentation.

To test your own modules, they can be cross-compiled for the target platform and tested directly on the
target. How this is done is described in the next section. As soon as the test phase is completed, the
EVerest module can be integrated into your firmware image.

In general, there are two ways to create customized firmware images. Either you create a complete Yocto
image based on the layers provided by chargebyte. Or, as already described in the Cross-compilation of
EVerest modules section, you cross-compile individual EVerest modules, integrate them into an already
existing mounted root file system and create an installable rauc image.

Building a complete Yocto image is the recommended way to create customized firmware images. It is more
complex to set up the Yocto build environment, but it is the most flexible way to create customized
firmware images. Adding individual EVerest modules to an already existing mounted root file system is easier to set up,
but less flexible. It is recommended if you only need to make minor changes to the firmware image (e.g.
adding a new EVerest module).

In summary, for more complex projects, the second approach is typically used to test smaller changes to the image,
while the first approach is used to create production-ready images. The following sections describe the
first option in detail. For the second option, see the section :ref:`creating_of_custom_firmware_images`.
