#include <arpa/inet.h>
#include <gtk/gtk.h>

#include "NinePatchPaintable.h"

enum {
	// The 9 patch segment is not a solid color.
	NO_COLOR = 0x00000001,
	// The 9 patch segment is completely transparent.
	TRANSPARENT_COLOR = 0x00000000
};

static void ninepatch_paintable_snapshot(GdkPaintable *paintable, GdkSnapshot *snapshot, double width, double height)
{
	int i, j;
	NinePatchPaintable *ninepatch = NINEPATCH_PAINTABLE(paintable);
	struct Res_png_9patch *chunk = ninepatch->chunk;
	if (chunk) {
		int32_t *xDivs = (void *)chunk + chunk->xDivsOffset;
		int32_t *yDivs = (void *)chunk + chunk->yDivsOffset;
		int32_t *color = (void *)chunk + chunk->colorsOffset;
		float strech_factor_width = (width - (ninepatch->width - ninepatch->strechy_width)) / ninepatch->strechy_width;
		float strech_factor_height = (height - (ninepatch->height - ninepatch->strechy_height)) / ninepatch->strechy_height;

		graphene_rect_t rect;
		GdkRGBA rgba;
		for (j = 0, rect.origin.y = 0; j < chunk->numYDivs + 1; j++, rect.origin.y += rect.size.height) {
			int div_start = j ? yDivs[j - 1] : 0;
			int div_end = (j == chunk->numYDivs) ? ninepatch->height : yDivs[j];
			float patch_height = div_end - div_start;
			if (j % 2) // odd sections are stretchable
				patch_height *= strech_factor_height;
			rect.size.height = patch_height;
			if (!patch_height) // skip empty sections
				continue;
			for (i = 0, rect.origin.x = 0; i < chunk->numXDivs + 1; i++, rect.origin.x += rect.size.width) {
				int div_start = i ? xDivs[i - 1] : 0;
				int div_end = (i == chunk->numXDivs) ? ninepatch->width : xDivs[i];
				float patch_width = div_end - div_start;
				if (i % 2) // odd sections are stretchable
					patch_width *= strech_factor_width;
				rect.size.width = patch_width;
				if (!patch_width) // skip empty sections
					continue;
				if (*color == NO_COLOR) {
					printf("NinePatchPaintable: warning NO_COLOR sections not yet implemented");
				} else if (*color != TRANSPARENT_COLOR) {
					rgba.red = (*color >> 24 & 0xFF) / 255.f;
					rgba.green = (*color >> 16 & 0xFF) / 255.f;
					rgba.blue = (*color >> 8 & 0xFF) / 255.f;
					rgba.alpha = (*color & 0xFF) / 255.f;
					gtk_snapshot_append_color(snapshot, &rgba, &rect);
				}
				color++;
			}
		}
	}
}

static GdkPaintableFlags ninepatch_paintable_get_flags(GdkPaintable *paintable)
{
	return GDK_PAINTABLE_STATIC_CONTENTS | GDK_PAINTABLE_STATIC_SIZE;
}

static void ninepatch_paintable_init(NinePatchPaintable *ninepatch_paintable)
{
}

static void ninepatch_paintable_paintable_init(GdkPaintableInterface *iface)
{
	iface->snapshot = ninepatch_paintable_snapshot;
	iface->get_flags = ninepatch_paintable_get_flags;
}

static void ninepatch_paintable_class_init(NinePatchPaintableClass *class)
{
}

G_DEFINE_TYPE_WITH_CODE(NinePatchPaintable, ninepatch_paintable, G_TYPE_OBJECT,
                        G_IMPLEMENT_INTERFACE(GDK_TYPE_PAINTABLE, ninepatch_paintable_paintable_init))

GdkPaintable *ninepatch_paintable_new(const char *path)
{
	struct Res_png_9patch *chunk = NULL;
	int width = 0;
	int height = 0;
	int strechy_width = 0;
	int strechy_height = 0;
	uint8_t buf[8];
	int i;
	FILE *f = fopen(path, "r");
	fread(buf, 1, 8, f);
	if (buf[0] != 0x89 || buf[1] != 'P' || buf[2] != 'N' || buf[3] != 'G') {
		return NULL;
	}
	while (!feof(f)) {
		fread(buf, 1, 8, f);
		int size = ntohl(((uint32_t *)buf)[0]);
		size += 4; // 4 bytes checksum

		if (!strncmp((char *)&buf[4], "npTc", 4)) {
			chunk = malloc(size);
			fread(chunk, 1, size, f);
			break;
		} else {
			fseek(f, size, SEEK_CUR);
		}
	}
	fclose(f);

	if (!chunk)
		return NULL;

	int32_t *xDivs = (void *)chunk + chunk->xDivsOffset;
	int32_t *yDivs = (void *)chunk + chunk->yDivsOffset;

	for (i = 0; i < chunk->numXDivs; i++)
		xDivs[i] = ntohl(xDivs[i]);
	for (i = 0; i < chunk->numYDivs; i++)
		yDivs[i] = ntohl(yDivs[i]);

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(path, NULL);
	width = gdk_pixbuf_get_width(pixbuf);
	height = gdk_pixbuf_get_height(pixbuf);
	g_object_unref(pixbuf);

	for (i = 1; i < chunk->numXDivs + 1; i += 2)
		strechy_width += (i == chunk->numXDivs ? width : xDivs[i]) - xDivs[i - 1];
	for (i = 1; i < chunk->numYDivs + 1; i += 2)
		strechy_height += (i == chunk->numYDivs ? height : yDivs[i]) - yDivs[i - 1];

	NinePatchPaintable *ninepatch = NINEPATCH_PAINTABLE(g_object_new(ninepatch_paintable_get_type(), NULL));
	ninepatch->chunk = chunk;
	ninepatch->width = width;
	ninepatch->height = height;
	ninepatch->strechy_width = strechy_width;
	ninepatch->strechy_height = strechy_height;
	return GDK_PAINTABLE(ninepatch);
}
