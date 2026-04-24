Basic Configuration
===================

In order to test EVerest, you need to build it either natively on host Linux machine or integrate it into a
firmware suitable for a specific target platform using Yocto. To build it natively, follow the instructions
found in the main EVerest repository "`everest <https://github.com/EVerest/EVerest>`_".
Additionally, there is a `Getting Started with EVerest guide <https://everest.github.io/nightly/how-to-guides/getting-started/>`_
which presents the different EVerest tools, build instructions, and first steps with EVerest.

For Yocto, EVerest offers "`meta-everest <https://github.com/EVerest/meta-everest>`_"; a Yocto meta layer
that can be used to integrate the EVerest charging stack into a platform-specific firmware image.
chargebyte utilizes this layer to produce firmware images suitable for chargebyte hardware platforms. Detailed instructions on
how to integrate EVerest into a chargebyte firmware image can be found on `GitHub <https://github.com/chargebyte/chargebyte-bsp/tree/kirkstone-everest>`_.

For setting up a use case with EVerest, such as basic setups for AC or DC charging, a YAML configuration file is needed.
Various example configurations, including those for software-in-the-loop tests, can be found in
the "`config <https://github.com/EVerest/EVerest/tree/main/config>`_" folder of the EVerest repository.
