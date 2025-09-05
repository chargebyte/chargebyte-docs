.. _development_preparation_checklist.inc:

Preparation Checklist for Development
=====================================

The following bullet points should be checked before starting with the development of a custom EVerest
module:

* Please make sure that your charge controller is started and running (see :ref:`getting_started.rst` chapter).
  It is recommended to connect the charge controller to the local computer via Ethernet. This makes it
  easier to share files (e.g. configuration, image, binary, or logging files) between the local computer
  and the charge controller.

* The EVerest development environment should be set up on the local Linux machine. Please follow the
  instructions in the EVerest documentation, in particular the chapter `Prepare Your Development Environment`_
  and the chapter `A Kind Of Quick Guide To EVerest`_.
  If you have problems setting up EVerest, please check the `Zulip chat`_
  to see whether this problem is already known and whether solutions have already been found.
  To verify that everything is installed correctly, EVerest should be compiled once natively on your
  system.

* Keep in mind that if you want to cross-compile an EVerest module, it must be compatible with the EVerest
  release used in the running firmware on the charge controller.
  Please have a look at the official `EVerest documentation`_ to learn how to check out a dedicated
  EVerest release.
  The everest-core version used by the firmware can be found in the release notes of the `firmware images`_.

.. _Prepare Your Development Environment: https://everest.github.io/nightly/general/02_detail_pre_setup.html
.. _A Kind Of Quick Guide To EVerest: https://everest.github.io/nightly/general/03_quick_start_guide.html
.. _Zulip chat: https://lfenergy.zulipchat.com/
.. _EVerest documentation: https://everest.github.io/nightly/dev_tools/edm.html#setting-up-and-updating-a-workspace
.. _firmware images: https://github.com/chargebyte/meta-chargebyte-everest/releases

.. note::

   All charge controllers shipped by chargebyte and the provided `firmware images`_ by chargebyte
   are currently based on Yocto kirkstone which includes Python 3.10. Since there exist some tooling
   dependencies during cross-compiling for the target platform, please use a Linux distribution on
   your host system which includes the very same Python version.
   This could be for example Ubuntu 22.04 LTS for Python 3.10.
