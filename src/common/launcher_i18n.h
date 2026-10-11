#pragma once

#ifdef __cplusplus
extern "C" {
#endif

const char* launcher_i18n_language(void);
const char* launcher_i18n_text(const char* english);
/* Switch the UI language at runtime ("it", "en"); NULL or "" goes back to the
 * build-time RECOMP_UI_LANGUAGE. */
void launcher_i18n_set_language(const char* code);

#ifdef __cplusplus
}
#endif
