.. _development_best_practices_everest_modules.inc:

Best Practices for Developing Custom EVerest Modules
====================================================

It is recommended to develop your custom software on your local PC Linux environment, using a compiler,
debugger, and tools that you are familiar with. Using tools like autotools, cmake, and pkg-config
in your own projects will make the integration and cross-compiling process much easier.

A native installation of EVerest on your host system is also recommended, as it includes simulation examples
that allow you to start and test EVerest locally on your machine. If the software you developed does
not depend on specific hardware components, it is also possible to test your EVerest module natively
on the local machine before it is executed on the target hardware platform.
Please refer to `Simulating EVerest <https://everest.github.io/nightly/how-to-guides/getting-started/get-started-sw.html#simulating-everest>`_
for more information on how to start your EVerest module in the SiL environment.

If you are starting your program from scratch and considering additional libraries to support specific
functionality, first review the libraries already required by EVerest or included in the firmware’s Linux
distribution. Minimizing dependencies helps reduce the size of the firmware update image, resulting in
faster transfer and flashing times during board updates.

When developing your software component, you need to decide how it will interact with the EVerest stack.
You can either implement your software as an EVerest module and use the internal interfaces to communicate
with the stack, or you can use an external API to interact with the EVerest stack.
The latter approach uses EVerest modules which provide an external API. Currently, there are two options
available:

* Using the `RpcApi module`_ to connect an energy management system via JSON-RPC over WebSocket.
* Using the `API module`_ to connect an energy management system via MQTT. Please note that this module
  is deprecated and will be removed in one of the next releases.

.. _RpcApi module: https://github.com/EVerest/EVerest/tree/main/modules/API/RpcApi
.. _API module: https://github.com/EVerest/EVerest/tree/main/modules/API/API

The advantage of not having to deal with the internal structures of EVerest (e.g. setting up an EVerest
development environment) and using a more stable API comes with the disadvantage of being limited to
the signals and parameters of the external interface. If you want to access additional internal parameters,
you usually have to develop your own EVerest module.

.. note::
   In a future release, there will be EVerest API modules for most of the internal EVerest interfaces, which will
   provide a more stable MQTT API for external applications. This will make it easier to develop custom applications
   without the need to create an EVerest module.

The process of creating your own EVerest modules is described in the EVerest documentation:
`How to: Develop New Modules <https://everest.github.io/nightly/tutorials/develop-new-module.html>`_.

.. note::

   It is also possible to create your module directly in the EVerest repository in the modules directory.
   This is only recommended if you either want to work on a fork of the EVerest repository or if you want to
   contribute the module to the main EVerest project. In general, it is recommended to create your own module
   in a separate EVerest module repository as described in the EVerest documentation.

Once your own modules work as expected on your local machine, or if this is not possible e.g.
due to hardware dependencies, then it is time to cross-compile it for the target platform and test it
within the target environment. The cross-compile procedure is describe in
:ref:`development_cross_compiling_everest_modules`.

In a later development stage, all your custom modules need/should be included into your custom
firmware update image so that it is included during firmware updates. This is described in
:ref:`creating_custom_firmware_images`.

The following flowchart summarizes the best practices for developing custom EVerest modules:

.. image:: ../../includes/_static/images/everest_development_flow.drawio.svg
   :alt: Best Practices for Developing Custom EVerest Modules
   :align: center
