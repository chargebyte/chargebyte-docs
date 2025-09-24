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
Please refer to `Simulating EVerest <https://everest.github.io/nightly/tutorials/run_sil/>`_ for more information
on how to start your EVerest module in the SiL environment.

If you are starting your program from scratch and considering additional libraries to support specific
functionality, first review the libraries already required by EVerest or included in the firmware’s Linux
distribution. Minimizing dependencies helps reduce the size of the firmware update image, resulting in
faster transfer and flashing times during board updates.

When developing your software component, you need to decide how it will interact with the EVerest stack.
You can either implement your software as an EVerest module and use the internal interfaces to communicate
with the stack, or you can use the external MQTT-based EVerest API provided by the `API module`_
to access the EVerest stack. For energy management use cases, the second option
is certainly a valid approach. However, the standard and more flexible path is to create a dedicated EVerest
module. For energy management use cases, a websocket JSON-RPC-based approach to communicate with the
EVerest stack will be available in the near future. For more information, feel free to contact us.

.. _API module: https://github.com/EVerest/everest-core/tree/main/modules/API/API

The process of creating your own EVerest modules is described in the EVerest documentation:
`How to: Develop New Modules <https://everest.github.io/nightly/tutorials/new_modules/>`_.

.. note::

   It is also possible to create your module directly in the everest-core project in the modules directory.
   This is only recommended if you either want to work on a fork of everest-core or if you want to
   contribute the module to the EVerest core project. In general, it is recommended to create your own module
   in a separate EVerest module repository as described in the EVerest documentation.

Once your own modules works as expected on your local machine, or if this is not possible, then it is
time to cross-compile it for the target platform and test it within the target environment.
The cross-compile procedure is describe in :ref:`development_cross_compiling_everest_modules`.

In a later development stage, all your custom modules need/should be included into your custom

The following flowchart summarizes the best practices for developing custom EVerest modules:

.. image:: ../../includes/_static/images/everest_development_flow.drawio.svg
   :alt: Best Practices for Developing Custom EVerest Modules
   :align: center