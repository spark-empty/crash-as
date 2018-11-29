/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifdef USE_LCD
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Lcd.h"

#include "asdebug.h"

#ifdef USE_STDRT
#include "rthw.h"
#include "interrupt.h"
#else
#include "irq.h"
#endif
#ifdef USE_LVGL
#include "lvgl/lvgl.h"
#endif
/* ============================ [ MACROS	] ====================================================== */
#define ARM_PL110_BASE 0x10120000

#ifdef USE_LVGL
#define IRQ_PBA8_GIC_START		  32
#define IRQ_VERSATILEPB_MOUSE   (IRQ_PBA8_GIC_START + 4)

#define MOUSE_ADDRESS	(0x10007000)
#define MOUSE_IRQ_NUM	(IRQ_VERSATILEPB_MOUSE)
#define MOUSE_XMAX	   (800)
#define MOUSE_YMAX	   (480)

#define MOUSE_BUTTON_LEFT	(0x01)
#define MOUSE_BUTTON_RIGHT   (0x02)
#define MOUSE_BUTTON_MIDDLE  (0x04)
#define MOUSE_BUTTON_DOWN	(0x10)
#define MOUSE_BUTTON_UP	  (0x20)
#define MOUSE_BUTTON_MOVE	(0x40)
#define MOUSE_BUTTON_WHELL   (0x80)

#define AS_LOG_MOUSE 0
#endif
/* ============================ [ TYPES	 ] ====================================================== */
typedef enum {
	PL110_240x320_25MHZ,
	PL110_320x240_25MHZ,
	PL110_176x220_25MHZ,
	PL110_640x480_25MHZ,
	PL110_800x600_36MHZ,
	PL110_176x220_10MHZ,
	PL110_320x240_10MHZ
} pl110_DisplayResolution;

typedef struct {
	uint32_t timing_0;
	uint32_t timing_1;
	uint32_t timing_2;
	uint32_t timing_3;
	uint32_t upper_panel_base;
	uint32_t lower_panel_base;
	uint32_t mask_set_clear;
	uint32_t control;
} pl110_MMIO;

typedef struct {
	pl110_MMIO * mmio;
	uint32_t * frame_buffer;
	uint32_t width;
	uint32_t height;
} pl110_Info;

#ifdef USE_LVGL
enum {
	MOUSE_CR		= 0x00,
	MOUSE_STAT	  = 0x04,
	MOUSE_DATA	  = 0x08,
	MOUSE_CLKDIV	= 0x0c,
	MOUSE_IIR	   = 0x10,
};
struct mouse_pl050_pdata_t {
	uint32_t virt;
	int irq;
	int xmax, ymax;
	int xpos, ypos;
	unsigned char packet[4];
	int index;
	int obtn;
	int type;
};
#endif
/* ============================ [ DATAS	 ] ====================================================== */
static pl110_Info plInfo;
#ifdef USE_LVGL
static struct mouse_pl050_pdata_t mouse_data;
static boolean left_button_down = false;
static int16_t last_x = 0;
static int16_t last_y = 0;
#endif
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS	] ====================================================== */
static void pl110_setPixel(uint32_t x, uint32_t y, uint32_t color) {
	plInfo.frame_buffer[x + plInfo.width * y] = color;
}

static void pl110_setResolution(pl110_DisplayResolution resolution) {
	switch (resolution) {
		default:
		case PL110_640x480_25MHZ:
		plInfo.width = 640;
		plInfo.height = 480;
		plInfo.mmio->timing_0 = 0x3f1f3f9c;
		plInfo.mmio->timing_1 = 0x090b61df;
		plInfo.mmio->timing_2 = 0x067f1800;
		plInfo.mmio->mask_set_clear = 0x82b;
		break;
	}
}

static void pl110_init() {
	plInfo.mmio = (pl110_MMIO *)(ARM_PL110_BASE);
	plInfo.mmio->upper_panel_base = 0x200000;
	plInfo.frame_buffer = (uint32_t *)(plInfo.mmio->upper_panel_base);

	pl110_setResolution(PL110_640x480_25MHZ);

	uint32_t x, y = 0;
	for (y = 0; y < plInfo.height; y++)
		for (x = 0; x < plInfo.width; x++)
			pl110_setPixel(x, y, 0xff0000);
}
#ifdef USE_LVGL
static inline uint8_t read8(uint32_t addr)
{
	return (*((volatile uint8_t *)(addr)));
}

static inline void write8(uint32_t addr, uint8_t value)
{
	*((volatile uint8_t *)(addr)) = value;
}

static inline uint32_t read32(uint32_t addr)
{
	return (*((volatile uint32_t *)(addr)));
}

static inline void write32(uint32_t addr, uint32_t value)
{
	*((volatile uint32_t *)(addr)) = value;
}

static inline int kmi_write(struct mouse_pl050_pdata_t * pdat, uint8_t value)
{
	int timeout = 1000;

	while((read8(pdat->virt + MOUSE_STAT) & (1 << 6)) == 0 && timeout--);

	if(timeout)
	{
		write8(pdat->virt + MOUSE_DATA, value);
		while((read8(pdat->virt + MOUSE_STAT) & (1 << 4)) == 0);

		if(read8(pdat->virt + MOUSE_DATA) == 0xfa)
			return TRUE;
	}
	return FALSE;
}

static inline int kmi_read(struct mouse_pl050_pdata_t * pdat, uint8_t * value)
{
	if((read8(pdat->virt + MOUSE_STAT) & (1 << 4)))
	{
		*value = read8(pdat->virt + MOUSE_DATA);
		return TRUE;
	}
	return FALSE;
}

static void mouse_pl050_interrupt(void)
{
	struct mouse_pl050_pdata_t * pdat = (struct mouse_pl050_pdata_t *)&mouse_data;
	int x, y, relx, rely, delta;
	int btndown, btnup, btn;
	int status = 0;

	status = read8(pdat->virt + MOUSE_IIR);
	while(status & (1 << 0))
	{
		pdat->packet[pdat->index] = read8(pdat->virt + MOUSE_DATA);
		pdat->index = (pdat->index + 1) & 0x3;

		if(pdat->index == 0)
		{
			btn = pdat->packet[0] & 0x7;
			btndown = (btn ^ pdat->obtn) & btn;
			btnup = (btn ^ pdat->obtn) & pdat->obtn;
			pdat->obtn = btn;

			if(pdat->packet[0] & 0x10)
				relx = 0xffffff00 | pdat->packet[1];
			else
				relx = pdat->packet[1];

			if(pdat->packet[0] & 0x20)
				rely = 0xffffff00 | pdat->packet[2];
			else
				rely = pdat->packet[2];
			rely = -rely;

			delta = pdat->packet[3] & 0xf;
			if(delta == 0xf)
				delta = -1;

			if(relx != 0)
			{
				pdat->xpos = pdat->xpos + relx;
				if(pdat->xpos < 0)
					pdat->xpos = 0;
				if(pdat->xpos > pdat->xmax - 1)
					pdat->xpos = pdat->xmax - 1;
			}
			if(rely != 0)
			{
				pdat->ypos = pdat->ypos + rely;
				if(pdat->ypos < 0)
					pdat->ypos = 0;
				if(pdat->ypos > pdat->ymax - 1)
					pdat->ypos = pdat->ymax - 1;
			}
			x = pdat->xpos;
			y = pdat->ypos;

			last_x = x;
			last_y = y;

			if(btndown & (0x01 << 0)) {
				left_button_down = TRUE;
			}

			if(btnup & (0x01 << 0)) {
				left_button_down = FALSE;
			}

			ASLOG(MOUSE, "%s @(%d,%d)\n",left_button_down?"pressed":"released", x, y);
		}

		status = read8(pdat->virt + MOUSE_IIR);
	}
}

static boolean mouse_read(lv_indev_data_t * data)
{
	/*Store the collected data*/
	data->point.x = last_x;
	data->point.y = last_y;
	data->state = left_button_down ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

	return false;
}

static int mouse_init(void)
{
	uint8_t value;
	uint32_t id;

	uint32_t virt = MOUSE_ADDRESS;
	int irq = MOUSE_IRQ_NUM;

	struct mouse_pl050_pdata_t* pdat = &mouse_data;

	id = (((read32(virt + 0xfec) & 0xff) << 24) |
				((read32(virt + 0xfe8) & 0xff) << 16) |
				((read32(virt + 0xfe4) & 0xff) <<  8) |
				((read32(virt + 0xfe0) & 0xff) <<  0));

	if(((id >> 12) & 0xff) != 0x41 || (id & 0xfff) != 0x050)
	{
		ASLOG(MOUSE, "read id fail id:0x%08x\n", id);
		return -1;
	}
	ASLOG(MOUSE,"initialize mouse okay\n");
	memset(pdat, 0, sizeof(struct mouse_pl050_pdata_t));

	pdat->virt = virt;
	pdat->irq = irq;
	pdat->xmax = MOUSE_XMAX;
	pdat->ymax = MOUSE_YMAX;
	pdat->xpos = pdat->xmax / 2;
	pdat->ypos = pdat->ymax / 2;
	pdat->packet[0] = 0;
	pdat->packet[1] = 0;
	pdat->packet[2] = 0;
	pdat->packet[3] = 0;
	pdat->index = 0;
	pdat->obtn = 0;

	write8(pdat->virt + MOUSE_CLKDIV, 0);
	write8(pdat->virt + MOUSE_CR, (1 << 2));
	kmi_write(pdat, 0xff);
	kmi_read(pdat, &value);
	kmi_write(pdat, 0xf3);
	kmi_write(pdat, 200);
	kmi_write(pdat, 0xf3);
	kmi_write(pdat, 100);
	kmi_write(pdat, 0xf3);
	kmi_write(pdat, 80);
	kmi_write(pdat, 0xf2);
	kmi_read(pdat, &value);
	kmi_read(pdat, &value);
	kmi_write(pdat, 0xf3);
	kmi_write(pdat, 100);
	kmi_write(pdat, 0xe8);
	kmi_write(pdat, 0x02);
	kmi_write(pdat, 0xe6);
	kmi_write(pdat, 0xf4);
	kmi_read(pdat, &value);
	kmi_read(pdat, &value);
	kmi_read(pdat, &value);
	kmi_read(pdat, &value);
	write8(pdat->virt + MOUSE_CR, (1 << 2) | (1 << 4));

#ifdef USE_STDRT
	rt_hw_interrupt_install(pdat->irq, (rt_isr_handler_t)mouse_pl050_interrupt, (void *)pdat, "mouse");
	rt_hw_interrupt_unmask(pdat->irq);
#else
	irq_install_isr(pdat->irq, (isr_callback_t)mouse_pl050_interrupt);
	irq_enable_line(pdat->irq);
#endif

	return 0;
}

static void lcd_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color)
{
   /*Return if the area is out the screen*/
	if(x2 < 0) return;
	if(y2 < 0) return;
	if(x1 > plInfo.width - 1) return;
	if(y1 > plInfo.height - 1) return;

	/*Truncate the area to the screen*/
	int32_t act_x1 = x1 < 0 ? 0 : x1;
	int32_t act_y1 = y1 < 0 ? 0 : y1;
	int32_t act_x2 = x2 > plInfo.width - 1 ? plInfo.width - 1 : x2;
	int32_t act_y2 = y2 > plInfo.height - 1 ? plInfo.height - 1 : y2;

	int32_t x;
	int32_t y;
	uint32_t color24 = lv_color_to24(color);

	for(x = act_x1; x <= act_x2; x++) {
		for(y = act_y1; y <= act_y2; y++) {
			plInfo.frame_buffer[y * plInfo.width + x] = color24;
		}
	}
}

static void lcd_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
   /*Return if the area is out the screen*/
	if(x2 < 0) return;
	if(y2 < 0) return;
	if(x1 > plInfo.width - 1) return;
	if(y1 > plInfo.height - 1) return;

	/*Truncate the area to the screen*/
	int32_t act_x1 = x1 < 0 ? 0 : x1;
	int32_t act_y1 = y1 < 0 ? 0 : y1;
	int32_t act_x2 = x2 > plInfo.width - 1 ? plInfo.width - 1 : x2;
	int32_t act_y2 = y2 > plInfo.height - 1 ? plInfo.height - 1 : y2;

	int32_t x;
	int32_t y;

	for(y = act_y1; y <= act_y2; y++) {
		for(x = act_x1; x <= act_x2; x++) {
			plInfo.frame_buffer[y * plInfo.width + x] = lv_color_to24(*color_p);
			color_p++;
		}

		color_p += x2 - act_x2;
	}

}

static void lcd_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
	/*Return if the area is out the screen*/
	if(x2 < 0 || y2 < 0 || x1 > plInfo.width - 1 || y1 > plInfo.height - 1) {
		lv_flush_ready();
		return;
	}

	int32_t y;
#if LV_COLOR_DEPTH != 24
	int32_t x;
	for(y = y1; y <= y2; y++) {
		for(x = x1; x <= x2; x++) {
			plInfo.frame_buffer[y * plInfo.width + x] = lv_color_to24(*color_p);
			color_p++;
		}

	}
#else
	uint32_t w = x2 - x1 + 1;
	for(y = y1; y <= y2; y++) {
		memcpy(&plInfo.frame_buffer[y * plInfo.width + x1], color_p, w * sizeof(lv_color_t));

		color_p += w;
	}
#endif

	/*IMPORTANT! It must be called to tell the system the flush is ready*/
	lv_flush_ready();
}
#endif
/* ============================ [ FUNCTIONS ] ====================================================== */
void Lcd_Init(void)
{
	pl110_init();
}

void LCD_DrawPixel( uint32 x, uint32 y, uint32 color )
{
	pl110_setPixel(x, y, color);
}

#ifdef USE_LVGL
void lv_hw_dsp_init(void)
{
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.disp_flush = lcd_flush;
	disp_drv.disp_fill = lcd_fill;
	disp_drv.disp_map = lcd_map;
	lv_disp_drv_register(&disp_drv);
}

void lv_hw_mouse_init(void)
{
	lv_indev_drv_t indev_drv;
	lv_obj_t * cursor;
	lv_indev_t * indev;
	mouse_init();
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read = mouse_read;		 /*This function will be called periodically (by the library) to get the mouse position and state*/
	indev = lv_indev_drv_register(&indev_drv);
	cursor = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(cursor, "*");
	lv_indev_set_cursor(indev, cursor);
}
#endif
#endif /* USE_LCD */

