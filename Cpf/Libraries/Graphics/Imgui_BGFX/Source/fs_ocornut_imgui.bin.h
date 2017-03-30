static const uint8_t fs_ocornut_imgui_glsl[238] =
{
	0x46, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x05, 0x73, 0x5f, 0x74, 0x65, 0x78, // FSH........s_tex
	0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0xd3, 0x00, 0x00, 0x00, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, // ..........varyin
	0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, // g highp vec4 v_c
	0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, // olor0;.varying h
	0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, // ighp vec2 v_texc
	0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, // oord0;.uniform s
	0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x3b, 0x0a, // ampler2D s_tex;.
	0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, // void main ().{. 
	0x20, 0x6c, 0x6f, 0x77, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, //  lowp vec4 tmpva
	0x72, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x20, // r_1;.  tmpvar_1 
	0x3d, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x73, 0x5f, 0x74, // = texture2D (s_t
	0x65, 0x78, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, // ex, v_texcoord0)
	0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, // ;.  gl_FragColor
	0x20, 0x3d, 0x20, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x20, 0x2a, 0x20, 0x76, //  = (tmpvar_1 * v
	0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x29, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,             // _color0);.}...
};
static const uint8_t fs_ocornut_imgui_spv[1621] =
{
	0x46, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0x48, 0x06, 0x03, 0x02, 0x23, 0x07, // FSH.......H...#.
	0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x08, 0x00, 0x20, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........ `......
	0x11, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, // ................
	0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30, 0x00, 0x00, 0x00, 0x00, // GLSL.std.450....
	0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x04, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x42, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, // ....B...........
	0x42, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x61, 0x09, 0x00, 0x00, // B...........a...
	0x42, 0x67, 0x66, 0x78, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x00, 0x00, 0x00, // BgfxSampler2D...
	0x06, 0x00, 0x06, 0x00, 0x61, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x5f, 0x73, 0x61, // ....a.......m_sa
	0x6d, 0x70, 0x6c, 0x65, 0x72, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0x61, 0x09, 0x00, 0x00, // mpler.......a...
	0x01, 0x00, 0x00, 0x00, 0x6d, 0x5f, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x00, 0x00, 0x00, // ....m_texture...
	0x05, 0x00, 0x04, 0x00, 0xfe, 0x0e, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x00, 0x00, 0x00, // ........s_tex...
	0x05, 0x00, 0x06, 0x00, 0x0f, 0x0d, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x53, 0x61, 0x6d, // ........s_texSam
	0x70, 0x6c, 0x65, 0x72, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x4b, 0x0f, 0x00, 0x00, // pler........K...
	0x73, 0x5f, 0x74, 0x65, 0x78, 0x54, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x00, 0x00, 0x00, 0x00, // s_texTexture....
	0x05, 0x00, 0x04, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x24, 0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x00, // ........$Global.
	0x06, 0x00, 0x06, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x76, 0x69, // ............u_vi
	0x65, 0x77, 0x52, 0x65, 0x63, 0x74, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0xaf, 0x09, 0x00, 0x00, // ewRect..........
	0x01, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x00, // ....u_viewTexel.
	0x06, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x76, 0x69, // ............u_vi
	0x65, 0x77, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // ew..............
	0x75, 0x5f, 0x69, 0x6e, 0x76, 0x56, 0x69, 0x65, 0x77, 0x00, 0x00, 0x00, 0x06, 0x00, 0x05, 0x00, // u_invView.......
	0xaf, 0x09, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x70, 0x72, 0x6f, 0x6a, 0x00, 0x00, // ........u_proj..
	0x06, 0x00, 0x06, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x69, 0x6e, // ............u_in
	0x76, 0x50, 0x72, 0x6f, 0x6a, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0xaf, 0x09, 0x00, 0x00, // vProj...........
	0x06, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x00, 0x00, // ....u_viewProj..
	0x06, 0x00, 0x07, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x69, 0x6e, // ............u_in
	0x76, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x00, 0x00, 0x00, 0x06, 0x00, 0x05, 0x00, // vViewProj.......
	0xaf, 0x09, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x00, // ........u_model.
	0x06, 0x00, 0x06, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x6d, 0x6f, // ............u_mo
	0x64, 0x65, 0x6c, 0x56, 0x69, 0x65, 0x77, 0x00, 0x06, 0x00, 0x07, 0x00, 0xaf, 0x09, 0x00, 0x00, // delView.........
	0x0a, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x56, 0x69, 0x65, 0x77, 0x50, // ....u_modelViewP
	0x72, 0x6f, 0x6a, 0x00, 0x06, 0x00, 0x06, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, // roj.............
	0x75, 0x5f, 0x61, 0x6c, 0x70, 0x68, 0x61, 0x52, 0x65, 0x66, 0x34, 0x00, 0x47, 0x00, 0x04, 0x00, // u_alphaRef4.G...
	0x0f, 0x0d, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, // ....".......G...
	0x0f, 0x0d, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, // ....!.......G...
	0x4b, 0x0f, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, // K...".......G...
	0x4b, 0x0f, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, // K...!.......G...
	0xfb, 0x09, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, // ........@...H...
	0xaf, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........#.......
	0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, // H...........#...
	0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // ....H...........
	0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // ....H...........
	0x23, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, // #... ...H.......
	0x02, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, // ............H...
	0xaf, 0x09, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, // ............H...
	0xaf, 0x09, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, // ........#...`...
	0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, // H...............
	0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, // ....H...........
	0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, // ....H...........
	0x23, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, // #.......H.......
	0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, // ............H...
	0xaf, 0x09, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, // ............H...
	0xaf, 0x09, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, // ........#.......
	0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, // H...............
	0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, // ....H...........
	0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, // ....H...........
	0x23, 0x00, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, // #... ...H.......
	0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, // ............H...
	0xaf, 0x09, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, // ............H...
	0xaf, 0x09, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00, // ........#...`...
	0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, // H...............
	0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, // ....H...........
	0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, // ....H...........
	0x23, 0x00, 0x00, 0x00, 0xa0, 0x01, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, // #.......H.......
	0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, // ............H...
	0xaf, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, // ............H...
	0xaf, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0xa0, 0x09, 0x00, 0x00, // ........#.......
	0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, // H...............
	0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, // ....H...........
	0x04, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, // ....H...........
	0x23, 0x00, 0x00, 0x00, 0xe0, 0x09, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0xaf, 0x09, 0x00, 0x00, // #.......H.......
	0x0a, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, // ............H...
	0xaf, 0x09, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x20, 0x0a, 0x00, 0x00, // ........#... ...
	0x47, 0x00, 0x03, 0x00, 0xaf, 0x09, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, // G...............
	0x08, 0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 0x02, 0x05, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, // ....!...........
	0x1a, 0x00, 0x02, 0x00, 0xfc, 0x01, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x0d, 0x00, 0x00, 0x00, // ................
	0x20, 0x00, 0x00, 0x00, 0x19, 0x00, 0x09, 0x00, 0x96, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, //  ...............
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x04, 0x00, 0x61, 0x09, 0x00, 0x00, // ............a...
	0xfc, 0x01, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x1b, 0x00, 0x00, 0x00, // ........ .......
	0x00, 0x00, 0x00, 0x00, 0x61, 0x09, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x1b, 0x00, 0x00, 0x00, // ....a...;.......
	0xfe, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x79, 0x04, 0x00, 0x00, // ........ ...y...
	0x00, 0x00, 0x00, 0x00, 0xfc, 0x01, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x79, 0x04, 0x00, 0x00, // ........;...y...
	0x0f, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x13, 0x03, 0x00, 0x00, // ........ .......
	0x00, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x13, 0x03, 0x00, 0x00, // ........;.......
	0x4b, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x1d, 0x00, 0x00, 0x00, // K...............
	0x0d, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x18, 0x00, 0x04, 0x00, 0x65, 0x00, 0x00, 0x00, // ............e...
	0x1d, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, // ................
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, //  .......+.......
	0x6a, 0x0a, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x04, 0x00, 0xfb, 0x09, 0x00, 0x00, // j... ...........
	0x65, 0x00, 0x00, 0x00, 0x6a, 0x0a, 0x00, 0x00, 0x1e, 0x00, 0x0e, 0x00, 0xaf, 0x09, 0x00, 0x00, // e...j...........
	0x1d, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, // ........e...e...
	0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, // e...e...e...e...
	0xfb, 0x09, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, // ....e...e.......
	0x36, 0x00, 0x05, 0x00, 0x08, 0x00, 0x00, 0x00, 0x42, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 6.......B.......
	0x02, 0x05, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x1f, 0x60, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, // .........`..=...
	0xfc, 0x01, 0x00, 0x00, 0x7b, 0x52, 0x00, 0x00, 0x0f, 0x0d, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, // ....{R......=...
	0x96, 0x00, 0x00, 0x00, 0x18, 0x50, 0x00, 0x00, 0x4b, 0x0f, 0x00, 0x00, 0x50, 0x00, 0x05, 0x00, // .....P..K...P...
	0x61, 0x09, 0x00, 0x00, 0x52, 0x2e, 0x00, 0x00, 0x7b, 0x52, 0x00, 0x00, 0x18, 0x50, 0x00, 0x00, // a...R...{R...P..
	0x3e, 0x00, 0x03, 0x00, 0xfe, 0x0e, 0x00, 0x00, 0x52, 0x2e, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, // >.......R.......
	0x38, 0x00, 0x01, 0x00, 0x00,                                                                   // 8....
};
static const uint8_t fs_ocornut_imgui_dx9[229] =
{
	0x46, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x05, 0x73, 0x5f, 0x74, 0x65, 0x78, // FSH........s_tex
	0x30, 0x01, 0x00, 0x00, 0x01, 0x00, 0xcc, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, 0xff, 0x1f, 0x00, // 0...............
	0x43, 0x54, 0x41, 0x42, 0x1c, 0x00, 0x00, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, // CTAB....O.......
	0x01, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, // ............H...
	0x30, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x38, 0x00, 0x00, 0x00, // 0...........8...
	0x00, 0x00, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x00, 0xab, 0xab, 0x04, 0x00, 0x0c, 0x00, // ....s_tex.......
	0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x73, 0x5f, 0x33, // ............ps_3
	0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, // _0.Microsoft (R)
	0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, //  HLSL Shader Com
	0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, 0x31, 0x30, 0x2e, 0x31, 0x00, 0xab, 0x1f, 0x00, 0x00, 0x02, // piler 10.1......
	0x0a, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x05, 0x00, 0x00, 0x80, // ................
	0x01, 0x00, 0x03, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x90, 0x00, 0x08, 0x0f, 0xa0, // ................
	0x42, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0x90, 0x00, 0x08, 0xe4, 0xa0, // B...............
	0x05, 0x00, 0x00, 0x03, 0x00, 0x08, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0x80, 0x00, 0x00, 0xe4, 0x90, // ................
	0xff, 0xff, 0x00, 0x00, 0x00,                                                                   // .....
};
static const uint8_t fs_ocornut_imgui_dx11[396] =
{
	0x46, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x01, 0x00, 0x05, 0x73, 0x5f, 0x74, 0x65, 0x78, // FSH........s_tex
	0x30, 0x01, 0x00, 0x00, 0x01, 0x00, 0x70, 0x01, 0x44, 0x58, 0x42, 0x43, 0xbe, 0x78, 0xe7, 0xa5, // 0.....p.DXBC.x..
	0x19, 0x0c, 0x70, 0xeb, 0x4c, 0xb1, 0xac, 0x1f, 0x16, 0x84, 0xe9, 0x97, 0x01, 0x00, 0x00, 0x00, // ..p.L...........
	0x70, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, // p.......,.......
	0xd4, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x4e, 0x6c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // ....ISGNl.......
	0x08, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // ....P...........
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // ................
	0x0f, 0x0f, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ....b...........
	0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, // ............SV_P
	0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x54, 0x45, // OSITION.COLOR.TE
	0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0xab, 0x4f, 0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, // XCOORD..OSGN,...
	0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........ .......
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, // ................
	0x53, 0x56, 0x5f, 0x54, 0x41, 0x52, 0x47, 0x45, 0x54, 0x00, 0xab, 0xab, 0x53, 0x48, 0x44, 0x52, // SV_TARGET...SHDR
	0x94, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x5a, 0x00, 0x00, 0x03, // ....@...%...Z...
	0x00, 0x60, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x18, 0x00, 0x04, 0x00, 0x70, 0x10, 0x00, // .`......X....p..
	0x00, 0x00, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x62, 0x10, 0x00, 0x03, 0xf2, 0x10, 0x10, 0x00, // ....UU..b.......
	0x01, 0x00, 0x00, 0x00, 0x62, 0x10, 0x00, 0x03, 0x32, 0x10, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, // ....b...2.......
	0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x02, // e.... ......h...
	0x01, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x09, 0xf2, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ....E...........
	0x46, 0x10, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x46, 0x7e, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // F.......F~......
	0x00, 0x60, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x07, 0xf2, 0x20, 0x10, 0x00, // .`......8.... ..
	0x00, 0x00, 0x00, 0x00, 0x46, 0x0e, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x1e, 0x10, 0x00, // ....F.......F...
	0x01, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,                         // ....>.......
};
static const uint8_t fs_ocornut_imgui_mtl[570] =
{
	0x46, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0x2b, 0x02, 0x00, 0x00, 0x75, 0x73, // FSH.......+...us
	0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65, 0x20, 0x6d, 0x65, // ing namespace me
	0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, // tal;.struct xlat
	0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x20, 0x7b, // MtlShaderInput {
	0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, // .  float4 v_colo
	0x72, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x32, 0x20, 0x76, 0x5f, 0x74, // r0;.  float2 v_t
	0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, // excoord0;.};.str
	0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, // uct xlatMtlShade
	0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, // rOutput {.  floa
	0x74, 0x34, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x3b, // t4 gl_FragColor;
	0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, // .};.struct xlatM
	0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, // tlShaderUniform 
	0x7b, 0x0a, 0x7d, 0x3b, 0x0a, 0x66, 0x72, 0x61, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x78, 0x6c, // {.};.fragment xl
	0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, // atMtlShaderOutpu
	0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x78, // t xlatMtlMain (x
	0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, // latMtlShaderInpu
	0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x20, 0x5b, 0x5b, 0x73, 0x74, 0x61, 0x67, 0x65, // t _mtl_i [[stage
	0x5f, 0x69, 0x6e, 0x5d, 0x5d, 0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, 0x20, // _in]], constant 
	0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, // xlatMtlShaderUni
	0x66, 0x6f, 0x72, 0x6d, 0x26, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x20, 0x5b, 0x5b, 0x62, // form& _mtl_u [[b
	0x75, 0x66, 0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x0a, 0x20, 0x20, 0x2c, 0x20, 0x20, // uffer(0)]].  ,  
	0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x64, 0x3c, 0x66, 0x6c, 0x6f, 0x61, 0x74, //  texture2d<float
	0x3e, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x20, 0x5b, 0x5b, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, // > s_tex [[textur
	0x65, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x2c, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x20, // e(0)]], sampler 
	0x5f, 0x6d, 0x74, 0x6c, 0x73, 0x6d, 0x70, 0x5f, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x20, 0x5b, 0x5b, // _mtlsmp_s_tex [[
	0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, // sampler(0)]]).{.
	0x20, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, //   xlatMtlShaderO
	0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x20, 0x20, // utput _mtl_o;.  
	0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, // _mtl_o.gl_FragCo
	0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x2e, 0x73, 0x61, 0x6d, // lor = (s_tex.sam
	0x70, 0x6c, 0x65, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x73, 0x6d, 0x70, 0x5f, 0x73, 0x5f, 0x74, 0x65, // ple(_mtlsmp_s_te
	0x78, 0x2c, 0x20, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x32, 0x29, 0x28, 0x5f, 0x6d, 0x74, 0x6c, // x, (float2)(_mtl
	0x5f, 0x69, 0x2e, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x29, // _i.v_texcoord0))
	0x20, 0x2a, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x2e, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, //  * _mtl_i.v_colo
	0x72, 0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x5f, 0x6d, // r0);.  return _m
	0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                     // tl_o;.}...
};
extern const uint8_t* fs_ocornut_imgui_pssl;
extern const uint32_t fs_ocornut_imgui_pssl_size;