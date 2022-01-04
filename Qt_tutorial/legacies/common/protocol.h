#pragma once

#define QCEF_SCHEMA "qcef"
#define QCEF_QUERY_NAME "QCefQuery"
#define QCEF_QUERY_CANCEL_NAME "QCefQueryCancel"
#define QCEF_OBJECT_NAME "QCefClient"
#define QCEF_BRIDGE_OBJ_NAME_KEY "bridge-obj-name"
#define QCEF_INVOKEMETHOD "invokeMethod"
#define QCEF_ADDEVENTLISTENER "addEventListener"
#define QCEF_REMOVEEVENTLISTENER "removeEventListener"

/// <summary>
/// this message is sent from render process to browser process
/// and is processed in the Qt UI thread
///
/// format
/// msg.name
///   msg.arg[0]: frame id
///   msg.arg[1]: function name
///   msg.arg[2~...]: function parameters
/// </summary>
#define INVOKEMETHOD_NOTIFY_MESSAGE "QCefClient#InvokeMethodNotify"

/// <summary>
/// this message is sent from browser process to render process
/// and is processed in the CefRenderer_Main thread
///
/// format:
///   msg.name:
///	  msg.arg[0]: frame id
///	  msg.arg[1]: function name
///	  msg.arg[2~...]: function parameters
/// </summary>
#define TRIGGEREVENT_NOTIFY_MESSAGE "QCefClient#TriggerEventNotify"

#define RENDER_PROCESS_NAME "QCefWing.exe"
#define RESOURCE_DIRECTORY_NAME "resources"
#define LOCALES_DIRECTORY_NAME "locales"

#define QCEF_USER_AGENT "START/1.0 (Windows; en-us)"
