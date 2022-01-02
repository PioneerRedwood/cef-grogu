// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include <cstring>

#include "cefclient/browser/resource.h"

namespace client {

int GetResourceId(const char* resource_name) {
  // Map of resource labels to BINARY id values.
  static struct _resource_map {
    const char* name;
    int id;
  } resource_map[] = {
      {"logo.png", IDS_LOGO_PNG},
      {"other_tests.html", IDS_OTHER_TESTS_HTML},
      {"response_filter.html", IDS_RESPONSE_FILTER_HTML},
      {"server.html", IDS_SERVER_HTML},
      {"urlrequest.html", IDS_URLREQUEST_HTML},
      {"websocket.html", IDS_WEBSOCKET_HTML},
      // grogu
      // {"grogu.html", IDS_GROGU_HTML},
  };

  for (size_t i = 0; i < sizeof(resource_map) / sizeof(_resource_map); ++i) {
    if (!strcmp(resource_map[i].name, resource_name))
      return resource_map[i].id;
  }

  return 0;
}

}  // namespace client
