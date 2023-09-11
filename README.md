# libONVIF

| os      | os_build | Status                                                                                                                                                                                                                                                                                                                                        |
| ------- | -------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Android | Linux    | [![Build Status](https://dev.azure.com/bjoernstresing/bjoernstresing/_apis/build/status/Tereius.libONVIF?repoName=Tereius%2FlibONVIF&branchName=master&jobName=Android&configuration=Android%20armv7Linux)](https://dev.azure.com/bjoernstresing/bjoernstresing/_build/latest?definitionId=7&repoName=Tereius%2FlibONVIF&branchName=master)   |
| Android | Windows  | [![Build Status](https://dev.azure.com/bjoernstresing/bjoernstresing/_apis/build/status/Tereius.libONVIF?repoName=Tereius%2FlibONVIF&branchName=master&jobName=Android&configuration=Android%20armv7Windows)](https://dev.azure.com/bjoernstresing/bjoernstresing/_build/latest?definitionId=7&repoName=Tereius%2FlibONVIF&branchName=master) |
| Linux   | Linux    | [![Build Status](https://dev.azure.com/bjoernstresing/bjoernstresing/_apis/build/status/Tereius.libONVIF?repoName=Tereius%2FlibONVIF&branchName=master&jobName=Linux)](https://dev.azure.com/bjoernstresing/bjoernstresing/_build/latest?definitionId=7&repoName=Tereius%2FlibONVIF&branchName=master)                                        |
| Windows | Windows  | [![Build Status](https://dev.azure.com/bjoernstresing/bjoernstresing/_apis/build/status/Tereius.libONVIF?repoName=Tereius%2FlibONVIF&branchName=master&jobName=Windows)](https://dev.azure.com/bjoernstresing/bjoernstresing/_build/latest?definitionId=7&repoName=Tereius%2FlibONVIF&branchName=master)                                      |
| Macos   | Macos    | [![Build Status](https://dev.azure.com/bjoernstresing/bjoernstresing/_apis/build/status/Tereius.libONVIF?repoName=Tereius%2FlibONVIF&branchName=master&jobName=Macos)](https://dev.azure.com/bjoernstresing/bjoernstresing/_build/latest?definitionId=7&repoName=Tereius%2FlibONVIF&branchName=master)                                        |

### Yet another ONVIF library

What does ONVIF stand for:

> ONVIF (Open Network Video Interface Forum) is a global and open industry forum with the goal of facilitating the development and use of a global open standard for the interface of physical IP-based security products – or, in other words, to create a standard for how IP products within video surveillance and other physical security areas can communicate with each other. [Wikipedia](https://en.wikipedia.org/wiki/ONVIF)

The idea behind this library is to hide some complexity of gsoap and to provide 'high level' classes including QT5 goodness. Currently there are eleven client side service methods implemented:

- ONVIF analytics http://www.onvif.org/ver20/analytics/wsdl
- ONVIF device http://www.onvif.org/ver10/device/wsdl
- ONVIF display http://www.onvif.org/ver10/display/wsdl
- ONVIF event http://www.onvif.org/ver10/events/wsdl
- ONVIF imaging http://www.onvif.org/ver20/imaging/wsdl
- ONVIF media http://www.onvif.org/ver10/media/wsdl
- ONVIF media2 http://www.onvif.org/ver20/media/wsdl
- ONVIF ptz http://www.onvif.org/ver20/ptz/wsdl
- ONVIF receiver http://www.onvif.org/ver10/receiver/wsdl
- ONVIF recording http://www.onvif.org/ver10/recording/wsdl
- ONVIF replay http://www.onvif.org/ver10/replay/wsdl

For every service exists a class following the naming scheme `Onvif*Client` (\* matches service name). These classes handle the RPCs. For the convenience of WS discovery and ONVIF (pull point) event handling there are two more classes: `OnvifDiscovery` and `OnvifPullPoint`.

Design thoughts:

- The most of this library is thread safe and should work in a multithreaded environment
- gsoap is 'hidden' from the user as much as possible
- RAII classes `Request<>`, `Response<>` wrapping the RPC parameters are responsible for the memory management

### Further reading

- The library comes with a small application (named ovifinfo) that does some device-discovery, inspection. You may want to look at the [source code](https://github.com/Tereius/libONVIF/blob/master/src/main.cpp).
- If you want to learn more about how to use libONVIF in a qml app take a look at the following project [ONVIFMonitor](https://github.com/Tereius/ONVIFMonitor).
- It is always advisable to look at the [ONVIF programmers guide](https://www.onvif.org/wp-content/uploads/2016/12/ONVIF_WG-APG-Application_Programmers_Guide-1.pdf) to learn more about ONVIF.
