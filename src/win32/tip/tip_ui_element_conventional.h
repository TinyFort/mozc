// Copyright 2010-2013, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MOZC_WIN32_TIP_TIP_UI_ELEMENT_CONVENTIONAL_H_
#define MOZC_WIN32_TIP_TIP_UI_ELEMENT_CONVENTIONAL_H_

#include <Windows.h>

#include "base/port.h"

struct ITfContext;
struct ITfUIElement;

namespace mozc {
namespace win32 {
namespace tsf {

class TipTextService;

class TipUiElementConventional {
 public:
  enum UIType {
    // The UI element is a suggest window whose contents is not observable
    // from the application and no candidate UI notifications will not be
    // generated.
    kUnobservableSuggestWindow,
    // The UI element is a suggest window whose contents is observable from
    // the application and candidate UI notifications will be generated
    // as if the window is a candidate window.
    kObservableSuggestWindow,
    // The UI element is a candidate window whose contents is observable from
    // the application and candidate UI notifications will be generated.
    kCandidateWindow,
  };

  // Returns a ITfUIElement object based of the given parameters. Caller must
  // maintain the reference count of the object returned.
  static ITfUIElement *New(UIType type,
                           TipTextService *text_service,
                           ITfContext *contxt);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(TipUiElementConventional);
};

}  // namespace tsf
}  // namespace win32
}  // namespace mozc

#endif  // MOZC_WIN32_TIP_TIP_UI_ELEMENT_CONVENTIONAL_H_
