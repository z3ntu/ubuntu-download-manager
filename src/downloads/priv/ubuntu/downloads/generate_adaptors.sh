echo "Generating adaptors from DBus xml definitions:"
echo "DownloadManagerAdaptor..."
qdbusxml2cpp -c DownloadManagerAdaptor -a download_manager_adaptor.h:download_manager_adaptor.cpp -i metatypes.h com.canonical.applications.download_manager.xml
echo "generated"
echo "DownloadAdaptor..."
qdbusxml2cpp -c DownloadAdaptor -a download_adaptor.h:download_adaptor.cpp -i metatypes.h com.canonical.applications.download.xml
echo "generated"

echo "GroupDownloadAdaptor..."
qdbusxml2cpp -c GroupDownloadAdaptor -a group_download_adaptor.h:group_download_adaptor.cpp -i metatypes.h com.canonical.applications.group_download.xml
echo "generated"

echo "DBusProxy"
qdbusxml2cpp -p dbus_proxy.h:dbus_proxy.cpp -c DBusProxy -i metatypes.h org.freedesktop.DBus.xml
echo "generated"
