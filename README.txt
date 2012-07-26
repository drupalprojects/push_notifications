The Push Notifications module provides the feature set to send out push
notifications to iOS (iPhone/iPad) and Android devices using Apple's
Push Notification Service (APNS) as well as Google's Android Cloud to Device
Messaging framework (C2DM) and or Google's Cloud Messaging for Android (GCM).
This module does not rely on any external services and allows site owners to
send out push notifications to any mobile device for free.

## REST Interface
Mobile apps can register the device by calling the REST interface provided by
the service module. Don't forget to enable the push_notifications resource.

{token} = The device token.
{type} = The type of the device - currently supported: ios or android.

---Register
URL: http://my-drupal-installation/services_module_endpoint/push_notifications
Method: "POST"
Payload: token={token}&type={type}

---Unregister
http://my-drupal-installation/services_module_endpoint/push_notifications/{token}
Method: "DELETE"
Payload:
