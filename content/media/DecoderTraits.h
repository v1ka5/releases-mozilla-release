/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef DecoderTraits_h_
#define DecoderTraits_h_

#include "nsCOMPtr.h"
#include "nsAString.h"

namespace mozilla {

class AbstractMediaDecoder;
class MediaDecoder;
class MediaDecoderOwner;
class MediaDecoderReader;

enum CanPlayStatus {
  CANPLAY_NO,
  CANPLAY_MAYBE,
  CANPLAY_YES
};

class DecoderTraits {
public:
  // Returns the CanPlayStatus indicating if we can handle this
  // MIME type. The MIME type should not include the codecs parameter.
  // That parameter should be passed in aCodecs, and will only be
  // used if whether a given MIME type being handled depends on the
  // codec that will be used.  If the codecs parameter has not been
  // specified, pass false in aHaveRequestedCodecs.
  static CanPlayStatus CanHandleMediaType(const char* aMIMEType,
                                          bool aHaveRequestedCodecs,
                                          const nsAString& aRequestedCodecs);

  // Returns true if we should handle this MIME type when it appears
  // as an <object> or as a toplevel page. If, in practice, our support
  // for the type is more limited than appears in the wild, we should return
  // false here even if CanHandleMediaType would return true.
  static bool ShouldHandleMediaType(const char* aMIMEType);

#ifdef MOZ_RAW
  static bool IsRawType(const nsACString& aType);
#endif

#ifdef MOZ_OGG
  static bool IsOggType(const nsACString& aType);
#endif

#ifdef MOZ_WAVE
  static bool IsWaveType(const nsACString& aType);
#endif

#ifdef MOZ_WEBM
  static bool IsWebMType(const nsACString& aType);
#endif

#ifdef MOZ_GSTREAMER
  // When enabled, use GStreamer for H.264, but not for codecs handled by our
  // bundled decoders, unless the "media.prefer-gstreamer" pref is set.
  static bool IsGStreamerSupportedType(const nsACString& aType);
  static bool IsH264Type(const nsACString& aType);
#endif

#ifdef MOZ_WIDGET_GONK
  static bool IsOmxSupportedType(const nsACString& aType);
#endif

#ifdef MOZ_MEDIA_PLUGINS
  static bool IsMediaPluginsType(const nsACString& aType);
#endif

#ifdef MOZ_DASH
  static bool IsDASHMPDType(const nsACString& aType);
#endif

#ifdef MOZ_WMF
  static bool IsWMFSupportedType(const nsACString& aType);
#endif

  // Create a decoder for the given aType. Returns null if we
  // were unable to create the decoder.
  static already_AddRefed<MediaDecoder> CreateDecoder(const nsACString& aType,
                                                      MediaDecoderOwner* aOwner);

  // Create a reader for thew given MIME type aType. Returns null
  // if we were unable to create the reader.
  static MediaDecoderReader* CreateReader(const nsACString& aType,
                                          AbstractMediaDecoder* aDecoder);

  // Returns true if MIME type aType is supported in video documents,
  // or false otherwise. Not all platforms support all MIME types, and
  // vice versa.
  static bool IsSupportedInVideoDocument(const nsACString& aType);
};

}

#endif

