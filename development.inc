***********
Development
***********

This chapter shows which options are available to customize the charge controller to your own needs. It
starts with creating your own EVerest modules that can be cross-compiled and run on the target, up to
creating complete customized firmware images that can be installed on the target.

.. note::
If you are developing an EVerest module that does not require special hardware interfaces, it is also possible
to test your module in the SIL environment of EVerest first. Please refer to "Simulating EVerest" 
<https://everest.github.io/nightly/general/03_quick_start_guide.html#quickstartguide-simulate> of the
EVerest Quick Start Guide.

Checklist before starting
=========================

The following bullet points should be checked before starting with the development of a custom EVerest
module:
#. Please make sure that your charge controller is started and running (":ref:`getting_started`"). It
   is recommended to connect the charge controller to the local computer via Ethernet. This makes it easier
   to share files (e.g., a configuration, image, binary, or logging files) between the local computer and the
   charge controller. Please follow the instructions in the ":ref:`getting_started`"
   chapter of this user guide.
#. The EVerest development environment should be set up on the local computer. Please follow the
   instructions in the EVerest documentation, in particular the chapter "Prepare Your Development Environment"
   <https://everest.github.io/nightly/general/02_detail_pre_setup.html> and
   the chapter "A Kind Of Quick Guide To EVerest" <https://everest.github.io/nightly/general/03_quick_start_guide.html>.
   If you have problems setting up EVerest, please check the Zulip chat (<https://lfenergy.zulipchat.com/>)
   to see whether this problem is already known and whether solutions have already been found.
#. Keep in mind that if you want to build a new EVerest module, it must be compatible with the EVerest
   release used in the firmware. Please have a look at the official `EVerest documentation <https://everest.github.io/nightly/dev_tools/edm.html#setting-up-and-updating-a-workspace>`_
   to learn how to check out a dedicated EVerest release. The everest-core version used by the firmware
   can be found in the release notes of the firmware image.
#. Please note that before you can start with this chapter, the EVerest development environment should be set
   up on the local machine. To check that everything is installed correctly, EVerest should be compiled once
   natively for your system.

   A native installation of EVerest is also recommended, as EVerest has some simulation examples installed,
   which can be used to start and test EVerest locally on your computer. Depending on the application,
   it is also possible to test your own EVerest module natively on the local machine before it is executed on the
   target hardware platform. Please refer to "Simulating EVerest" 
   <https://everest.github.io/nightly/general/03_quick_start_guide.html#quickstartguide-simulate> of the
   EVerest Quick Start Guide for more information on how to simulate EVerest on your local machine.
