--- chrome/browser/ui/chrome_pages.h.orig	2023-02-11 09:11:04 UTC
+++ chrome/browser/ui/chrome_pages.h
@@ -33,7 +33,7 @@ enum class ConsentLevel;
 }  // namespace signin
 
 #if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
-    BUILDFLAG(IS_FUCHSIA)
+    BUILDFLAG(IS_FUCHSIA) || BUILDFLAG(IS_BSD)
 namespace web_app {
 enum class AppSettingsPageEntryPoint;
 }  // namespace web_app
@@ -222,7 +222,7 @@ void ShowBrowserSigninOrSettings(Browser* browser,
 #endif
 
 #if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
-    BUILDFLAG(IS_FUCHSIA)
+    BUILDFLAG(IS_FUCHSIA) || BUILDFLAG(IS_BSD)
 // Show chrome://app-settings/<app-id> page.
 void ShowWebAppSettings(Browser* browser,
                         const std::string& app_id,
