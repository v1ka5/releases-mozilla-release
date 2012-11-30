# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

MOZ_APP_BASENAME=B2G
MOZ_APP_VENDOR=Mozilla

MOZ_APP_VERSION=18.0
MOZ_APP_UA_NAME=Firefox

MOZ_UA_OS_AGNOSTIC=1

MOZ_B2G_VERSION=1.0.0

MOZ_BRANDING_DIRECTORY=b2g/branding/unofficial
MOZ_OFFICIAL_BRANDING_DIRECTORY=b2g/branding/official
# MOZ_APP_DISPLAYNAME is set by branding/configure.sh

MOZ_SAFE_BROWSING=
MOZ_SERVICES_COMMON=1
MOZ_SERVICES_HEALTHREPORT=1
MOZ_SERVICES_METRICS=1

MOZ_WEBSMS_BACKEND=1
MOZ_DISABLE_DOMCRYPTO=1
MOZ_APP_STATIC_INI=1

if test "$OS_TARGET" = "Android"; then
MOZ_CAPTURE=1
MOZ_RAW=1
MOZ_AUDIO_CHANNEL_MANAGER=1
fi

# use custom widget for html:select
MOZ_USE_NATIVE_POPUP_WINDOWS=1

if test "$LIBXUL_SDK"; then
MOZ_XULRUNNER=1
else
MOZ_XULRUNNER=
fi

MOZ_APP_ID={3c2e2abc-06d4-11e1-ac3b-374f68613e61}
MOZ_EXTENSION_MANAGER=1

MOZ_SYS_MSG=1

MOZ_PAY=1
MOZ_TOOLKIT_SEARCH=
MOZ_PLACES=
MOZ_B2G=1
