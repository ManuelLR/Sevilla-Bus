#include <pebble.h>
#include <data.h>

#define PERSIST_KEY_TIMES_OPENED 0

static int s_opened = 0;
static char s_message[32];

static void prv_update_launch_data() {
	// Read and increment the number of times we've opened the app
	s_opened = persist_read_int(PERSIST_KEY_TIMES_OPENED) + 1;

	// Write the new value back to the persistent storage
	persist_write_int(PERSIST_KEY_TIMES_OPENED, s_opened);

	// Generate the display string
//	snprintf(s_message, 32, "Opened app %d time%c", s_opened,
//			s_opened == 1 ? '\0' : 's');
	if(get_bus_stop_detail() != NULL){
		snprintf(s_message, 32, "Last stop %s", get_bus_stop_detail()->number);
	}
}

static void prv_update_app_glance(AppGlanceReloadSession *session, size_t limit,
		void *context) {
	// This should never happen, but developers should always ensure
	// they’re not adding more app glance slices than the limit
	if (limit < 1)
		return;

	// Cast the context object to a string
	const char *message = (char *) context;

	// Create the AppGlanceSlice
	// When layout.icon is not set, the app's default icon is used
	const AppGlanceSlice entry = (AppGlanceSlice ) {
					.layout = {
							.icon = APP_GLANCE_SLICE_DEFAULT_ICON,
							.subtitle_template_string = message
					},
			// TODO: Change to APP_GLANCE_SLICE_NO_EXPIRATION in SDK 4-dp2
					.expiration_time = time(NULL) + 3600 };

	// Add the slice, and check the result
	const AppGlanceResult result = app_glance_add_slice(session, entry);
	if (result != APP_GLANCE_RESULT_SUCCESS) {
		APP_LOG(APP_LOG_LEVEL_ERROR, "AppGlance Error: %d", result);
	}
}


void glance_init(void) {
	prv_update_launch_data();
}

void glance_deinit(void) {
	app_glance_reload(prv_update_app_glance, s_message);
}
