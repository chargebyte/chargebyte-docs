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

* Please make sure that your charge controller is started and running (:ref:`getting_started.rst`).
  It is recommended to connect the charge controller to the local computer via Ethernet. This makes it
  easier to share files (e.g., configuration, image, binary, or logging files) between the local computer
  and the charge controller.

* The EVerest development environment should be set up on the local Linux machine. Please follow the
  instructions in the EVerest documentation, in particular the chapter `Prepare Your Development Environment <https://everest.github.io/nightly/general/02_detail_pre_setup.html>`_
  and the chapter `A Kind Of Quick Guide To EVerest <https://everest.github.io/nightly/general/03_quick_start_guide.html>`_.
  If you have problems setting up EVerest, please check the `Zulip chat <https://lfenergy.zulipchat.com/>`_
  to see whether this problem is already known and whether solutions have already been found.
  To verify that everything is installed correctly, EVerest should be compiled once natively for your
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

A native installation of EVerest is also recommended, as EVerest has some simulation examples installed,
which can be used to start and test EVerest locally on your computer. If the software you developed does not
depend on specific hardware components, it is also possible to test your EVerest module natively on the local
machine before it is executed on the target hardware platform. Please refer to `Simulating EVerest <https://everest.github.io/nightly/tutorials/run_sil/index.html>`_
for more information on how to start your EVerest module in the SiL environment.

If you start your project from scratch, have a look at libraries which are already required by the EVerest
stack and/or Linux distribution. Reuse these libraries to keep the overall firmware footprint small.
The benefit is that updating the boards will take less time to transfer the firmware update image
and flash it to internal storage.
You need to determine how your software components will interact with the EVerest stack. You can develop
your software as an EVerest module and use one of the EVerest interfaces for interaction. Alternatively,
you can utilize the simple MQTT-based API provided by the EVerest
`API <https://github.com/EVerest/everest-core/tree/main/modules/API>`_ module, which gives you access
to the EVerest stack internals. Refer to section :ref:`adding-a-custom-everest-module` to learn how to
create an EVerest module.

The process of creating your own EVerest modules is described in the EVerest documentation:
https://everest.github.io/nightly/tutorials/new_modules/index.html

.. note::
   It is also possible to create your module directly in the EVerest-core project in the modules directory. 
   This is only recommended if you either want to work on a fork of everest-core or if you want to
   contribute the module to the EVerest core project. In general, it is recommended to create your own module
   in a separate EVerest module repository as described in the EVerest documentation.
