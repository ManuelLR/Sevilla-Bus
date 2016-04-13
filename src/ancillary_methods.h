#pragma once

bool get_JS_is_ready(void);
void set_JS_is_ready(bool input);
void graphics_draw_text_vertically_center(GContext* ctx,
		const char* text, GFont const font, const GRect box,
		const GTextOverflowMode overflow_mode, const GTextAlignment alignment);

AppMessageResult ancillary_app_message_outbox_begin(
		DictionaryIterator **iterator);

AppMessageResult ancillary_app_message_outbox_send(void);

void draw_layout_border (GContext *ctx, GRect zoneToBorder, int strokeWidth, int difference, GColor color);