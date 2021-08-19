#LibSDLSamples

Document Design Goals:

To integrate an address lookup system which downloads .MVT files from OSRM local server and draw those map vector tiles to SDL rendered window

Mini Goals:

-Compile OSRM

-Extract North America into OSRM installation

-Setup virtual host using Apache to proxy back into the osrm-routing machine

-Retrieve MVT files for map nodes

-Extract coordinate data for a .MVT file

-Draw coordinates from the selected .MVT file

This project expects you to have OSRM somewhere either publically through the main website http://project-osrm.org/.

You can get started learning about OSRM here http://project-osrm.org/docs/v5.24.0/api/

This project also uses SDL to draw and render lines to the screen surface on top of a window