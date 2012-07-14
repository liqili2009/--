/*
项目:		激光测量
编写:		孙继东		SunJD99@Yahoo.com.cn
模块描述:	TFT显示程序定义
文件名:	tft.global.h
MCU:	STM32F10X		目前是STM32F101R8/STM32F103RB
开始时间:	2011-7-13 10:13:07
*/

//以下为宏定义

//以下为常量
//以下是显示字符有关
#define LINE_MIDDLE_HZ	(220 / 21)		//中汉字行数量
#define LINE_SMALL_HZ	(220 / 14)		//小汉字行数量
#define LINE_TINY_ASCII	(220 / 10)		//小汉字行数量
#define LINE_NUMBER	4			//数字行数量
#define QUANTITY_MIDDLE_HZ	(176 / 20)	//每行中汉字数量,
#define QUANTITY_SMALL_HZ	(176 / 12)		//每行小汉字数量
#define QUANTITY_NUMBER	6		//每行中字符数量
#define QUANTITY_MIDDLE_ASCII	(176 / 10)		//每行中字符数量
#define QUANTITY_SMALL_ASCII	(176 / 10)		//每行小字符数量
#define QUANTITY_TINY_ASCII	28		//(176 / 6)		//每行微字符数量

//以下是显示字符

//以下为存放在FLASH里面的图标,目前所有图片都放在FLASH里面
//以下为提示图标,左边一列
#define PROMPT_LENGTH_0_U			0	//单次0,选前
#define PROMPT_LENGTH_0_S			1	//单次0,选中
#define PROMPT_LENGTH_1_U			2	//单次1,选前
#define PROMPT_LENGTH_1_S			3	//单次1,选中
#define PROMPT_CONTINUE				4	//连续
#define PROMPT_CONTINUE_MAX_E		5	//连续,最大,英文
#define PROMPT_CONTINUE_MIN_E		6	//连续,最小,英文
#define PROMPT_CONTINUE_MAX_C		7	//连续,最大,中文
#define PROMPT_CONTINUE_MIN_C		8	//连续,最小,中文
#define PROMPT_AREA_X				9	//面积,长
#define PROMPT_AREA_X_U				10	//面积,长,选前
#define PROMPT_AREA_X_S				11	//面积,长,选中
#define PROMPT_AREA_Y				12	//面积,宽
#define PROMPT_AREA_Y_U				13	//面积,宽,选前
#define PROMPT_AREA_Y_S				14	//面积,宽,选中
#define PROMPT_AREA					15	//面积
#define PROMPT_AREA_PERIMETER		16	//面积,周长
#define PROMPT_VOL_Y				17	//体积,宽
#define PROMPT_VOL_Y_U				18	//体积,宽,选前
#define PROMPT_VOL_Y_S				19	//体积,宽,选中
#define PROMPT_VOL_FLOOR			20	//体积,底面积
#define PROMPT_VOL_FLOOR_S			21	//体积,底面积,选中
#define PROMPT_VOL_PERIMETER		22	//体积,底周长
#define PROMPT_VOL_PERIMETER_S		23	//体积,底周长,选中
#define PROMPT_VOL_Z				24	//体积,高
#define PROMPT_VOL_Z_U				25	//体积,高,选前
#define PROMPT_VOL_Z_S				26	//体积,高,选中
#define PROMPT_VOL_X				27	//体积,长
#define PROMPT_VOL_X_U				28	//体积,长,选前
#define PROMPT_VOL_X_S				29	//体积,长,选中
#define PROMPT_VOL_WALL				30	//体积,墙体面积
#define PROMPT_VOL_WALL_S				31	//体积,墙体面积,选中
#define PROMPT_VOLUME				32	//体积
#define PROMPT_GOUGU2				33	//勾股2
#define PROMPT_GOUGU2_AGL			34	//勾股2,夹角
#define PROMPT_GOUGU2_LVL			35	//勾股2,水平边
#define PROMPT_GOUGU2_LVL_U			36	//勾股2,水平边,选前
#define PROMPT_GOUGU2_LVL_S			37	//勾股2,水平边,选中
#define PROMPT_GOUGU2_SLP			38	//勾股2,斜边
#define PROMPT_GOUGU2_SLP_U			39	//勾股2,斜边,选前
#define PROMPT_GOUGU2_SLP_S			40	//勾股2,斜边,选中
#define PROMPT_GOUGU3				41	//勾股3
#define PROMPT_GOUGU3_ANGLE			42	//勾股3,夹角
#define PROMPT_GOUGU3_ANGLE_S		43	//勾股3,夹角,选中
#define PROMPT_GOUGU3_VET1			44	//勾股3,上垂直边
#define PROMPT_GOUGU3_VET1_S		45	//勾股3,上垂直边,选中
#define PROMPT_GOUGU3_SL1			46	//勾股3,上斜边
#define PROMPT_GOUGU3_SL1_U			47	//勾股3,上斜边,选前
#define PROMPT_GOUGU3_SL1_S			48	//勾股3,上斜边,选中
#define PROMPT_GOUGU3_LVL			49	//勾股3,水平边
#define PROMPT_GOUGU3_LVL_U			50	//勾股3,水平边,选前
#define PROMPT_GOUGU3_LVL_S			51	//勾股3,水平边,选中
#define PROMPT_GOUGU3_VET2			52	//勾股3,下垂直边
#define PROMPT_GOUGU3_VET2_S		53	//勾股3,下垂直边,选中
#define PROMPT_GOUGU3_SL2			54	//勾股3,下斜边
#define PROMPT_GOUGU3_SL2_U			55	//勾股3,下斜边,选前
#define PROMPT_GOUGU3_SL2_S			56	//勾股3,下斜边,选中
#define PROMPT_ANGLE				57	//角度
#define PROMPT_ANGLE_ANGLE			58	//角度,角度
#define PROMPT_ANGLE_SLOP			59	//角度,斜边
#define PROMPT_ANGLE_SLOP_U			60	//角度,斜边,选前
#define PROMPT_ANGLE_SLOP_S			61	//角度,斜边,选中
#define PROMPT_LEVEL_VET			62	//水平,垂直边
#define PROMPT_LEVEL_AGL			63	//水平,夹角
#define PROMPT_LEVEL				64	//水平
#define PROMPT_LEVEL_SLP			65	//水平,斜边
#define PROMPT_LEVEL_SLP_U			66	//水平,斜边,选前
#define PROMPT_LEVEL_SLP_S			67	//水平,斜边,选中
#define PROMPT_VERTICAL				68	//垂直
#define PROMPT_VERTICAL_ANGLE		69	//垂直,夹角
#define PROMPT_VERTICAL_ANGLE_S		70	//垂直,夹角,选中
#define PROMPT_VERTICAL_VET1		71	//垂直,上垂直边
#define PROMPT_VERTICAL_VET1_S		72	//垂直,上垂直边,选中
#define PROMPT_VERTICAL_SLP1_U		73	//垂直,上斜边,选前
#define PROMPT_VERTICAL_SLP1_S		74	//垂直,上斜边,选中
#define PROMPT_VERTICAL_SLP1		75	//垂直,上斜边
#define PROMPT_VERTICAL_VET2		76	//垂直,下垂直边
#define PROMPT_VERTICAL_VET2_S		77	//垂直,下垂直边,选中
#define PROMPT_VERTICAL_SLP2_U		78	//垂直,下斜边,选前
#define PROMPT_VERTICAL_SLP2_S		79	//垂直,下斜边,选中
#define PROMPT_VERTICAL_SLP2		80	//垂直,下斜边
#define PROMPT_TRIANGLE_B			81	//三角,第二边
#define PROMPT_TRIANGLE_B_U			82	//三角,第二边,选前
#define PROMPT_TRIANGLE_B_S			83	//三角,第二边,选中
#define PROMPT_TRIANGLE_C			84	//三角,第三边
#define PROMPT_TRIANGLE_C_U			85	//三角,第三边,选前
#define PROMPT_TRIANGLE_C_S			86	//三角,第三边,选中
#define PROMPT_TRIANGLE_A			87	//三角,第一边
#define PROMPT_TRIANGLE_A_U			88	//三角,第一边,选前
#define PROMPT_TRIANGLE_A_S			89	//三角,第一边,选中
#define PROMPT_TRIANGLE				90	//三角
#define PROMPT_TRIANGLE_PERMR		91	//三角,三角周长
#define PROMPT_TRIANGLE_PERMR_S		92	//三角,三角周长,选中
#define PROMPT_TRIANGLE_ANGLE		93	//三角,一二边夹角
#define PROMPT_TRIANGLE_ANGLE_S		94	//三角,一二边夹角,选中
#define PROMPT_LOFT_BIAS			95	//放样,偏差
#define PROMPT_LOFT					96	//放样
#define PROMPT_DELAY				97	//延时
#define PROMPT_MATH_EQUAL			98	//运算,等
#define PROMPT_MATH_PLUS			99	//运算,加
#define PROMPT_MATH_MINUS			100	//运算,减
#define PROMPT_MENU_TOOLS_U			101	//菜单,工具,选择
#define PROMPT_MENU_TOOLS			102	//菜单,工具
#define PROMPT_MENU_TOOLS_S			103	//菜单,工具,选中
#define PROMPT_MENU_SET_U			104	//菜单,设置,选择
#define PROMPT_MENU_SET				105	//菜单,设置
#define PROMPT_MENU_SET_S			106	//菜单,设置,选中
#define PROMPT_MENU_PERSON_U		107	//菜单,个人,选择
#define PROMPT_MENU_PERSON			108	//菜单,个人
#define PROMPT_MENU_PERSON_S		109	//菜单,个人,选中
#define PROMPT_MENU_OTHERS_U		110	//菜单,其它,选择
#define PROMPT_MENU_OTHERS			111	//菜单,其它
#define PROMPT_MENU_OTHERS_S		112	//菜单,其它,选中
#define PROMPT_RECORD_ALL_S			113	//记录,所有,选中
#define PROMPT_RECORD_ALL			114	//记录,所有
#define PROMPT_RECORD_ALL_U			115	//记录,所有,选择
#define PROMPT_RECORD_DISTANCE_S	116	//记录,距离,选中
#define PROMPT_RECORD_DISTANCE		117	//记录,距离
#define PROMPT_RECORD_DISTANCE_U	118	//记录,距离,选择
#define PROMPT_RECORD_AREA_S		119	//记录,面积,选中
#define PROMPT_RECORD_AREA			120	//记录,面积
#define PROMPT_RECORD_AREA_U		121	//记录,面积,选择
#define PROMPT_RECORD_ANGLE_S		122	//记录,角度,选中
#define PROMPT_RECORD_ANGLE			123	//记录,角度
#define PROMPT_RECORD_ANGLE_U		124	//记录,角度,选择
#define PROMPT_RECORD_LOCK_S		125	//记录,锁定,选中
#define PROMPT_RECORD_LOCK			126	//记录,锁定
#define PROMPT_RECORD_LOCK_U		127	//记录,锁定,选择
#define PROMPT_NULL					128	//空

//以下为提示左右,左边一列
#define ICON_PROMPT_UP_N	0
#define ICON_PROMPT_UP		1
#define ICON_PROMPT_DOWN_N	2
#define ICON_PROMPT_DOWN	3

//以下为类型左右,上边一行
#define ICON_TYPE_LEFT_N	0
#define ICON_TYPE_LEFT		1
#define ICON_TYPE_RIGHT_N	2
#define ICON_TYPE_RIGHT		3

//以下为类型图标,上边一行
#define TYPE_CONTINUE			0	//连续测量
#define TYPE_DELAY				1	//定时测量
#define TYPE_LOFT				2	//放样测量
#define TYPE_LENGTH				3	//单测图标
#define TYPE_AREA_RIGHT			4	//面积
#define TYPE_AREA_MIDDLE		5	//面积
#define TYPE_AREA_LEFT			6	//面积
#define TYPE_VOLUME_RIGHT		7	//体积
#define TYPE_VOLUME_MIDDLE		8	//体积
#define TYPE_VOLUME_LEFT		9	//体积
#define TYPE_G2_RIGHT			10	//勾股2
#define TYPE_G2_MIDDLE			11	//勾股2
#define TYPE_G2_LEFT			12	//勾股2
#define TYPE_G3_RIGHT			13	//勾股3
#define TYPE_G3_MIDDLE			14	//勾股3
#define TYPE_G3_LEFT			15	//勾股3
#define TYPE_ANGLE_RIGHT		16	//倾角
#define TYPE_ANGLE_MIDDLE		17	//倾角
#define TYPE_ANGLE_LEFT			18	//倾角
#define TYPE_LEVEL_RIGHT		19	//水平
#define TYPE_LEVEL_MIDDLE		20	//水平
#define TYPE_LEVEL_LEFT			21	//水平
#define TYPE_VERTICAL_RIGHT		22	//垂直
#define TYPE_VERTICAL_MIDDLE	23	//垂直
#define TYPE_VERTICAL_LEFT		24	//垂直
#define TYPE_TRIANGLE_RIGHT		25	//三角
#define TYPE_TRIANGLE_MIDDLE	26	//三角
#define TYPE_TRIANGLE_LEFT		27	//三角

//以下为放样提示图标
#define ICON_LOFT_FIXEDLY	0
#define ICON_LOFT_BACKWARD	1
#define ICON_LOFT_FORWARD	2

//以下为符号图标
#define SYMBOL_DEGREE_PLUS		0	//角度+
#define SYMBOL_DEGREE_MINUS		1	//角度-
#define SYMBOL_PLUS		2
#define SYMBOL_MINUS		3

//以下为其它图标
#define OTHER_ENGINEER		0	//3工程
#define OTHER_Y_BUBBLE		1	//10 垂直 气泡
#define OTHER_Y_GRADIENTER	2	//10 垂直 水柱
#define OTHER_X_BUBBLE		3	//10 水平 气泡
#define OTHER_X_GRADIENTER	4	//10 水平 水柱
#define OTHER_45_BUBBLE		5	//10 斜角 气泡
#define OTHER_45_GRADIENTER	6	//10 斜角 水柱
#define OTHER_OK			7	//ok
#define OTHER_OK_BUTTON		8	//OK 按钮
#define OTHER_USB			9	//USB
#define OTHER_MENU_RIGHT_U	10	//菜单 右 选前
#define OTHER_MENU_RIGHT_S	11	//菜单 右 选中
#define OTHER_ERROR_0		12	//错误解决 图标
#define OTHER_ERROR_1		13	//错误提醒 图标
#define OTHER_TOOLS_USB_0	14	//工具 数据导出02 中间图标
#define OTHER_TOOLS_USB_1	15	//工具 数据导出03 中间图标
#define OTHER_TOOLS_USB_2	16	//工具 数据导出04 中间图标
#define OTHER_RECORD_U		17	//记录 长条 选前
#define OTHER_RECORD_S		18	//记录 长条 选中
#define OTHER_RECORD_BACK	19	//记录 下部 左侧底图
#define OTHER_TYPE_BACK		20	//类型部分 底图
#define OTHER_BRIGHT_0		21	//亮度 空格
#define OTHER_BRIGHT_1		22	//亮度 满格
#define OTHER_OPTION_U		23	//钮 选前
#define OTHER_OPTION_S		24	//钮 选中
#define OTHER_DEVICE_0		25	//设备图标
#define OTHER_DEVICE_1		26	//设备旋转图标
#define OTHER_BUBBLE_0		27	//水平仪 管子
#define OTHER_BUBBLE_1		28	//水平仪 气泡
#define OTHER_THERMOMETER_0	29	//温度计 0
#define OTHER_THERMOMETER_1	30	//温度计 1
#define OTHER_THERMOMETER_2	31	//温度计 2
#define OTHER_THERMOMETER_3	32	//温度计上 底图
#define OTHER_THERMOMETER_4	33	//温度计下 底图
#define OTHER_PROMPT_BACK	34	//下部左侧 底图
#define OTHER_LOCK			35	//重要数据标志
#define OTHER_TITLE_BACK	36	//状态栏 底图

//以下为记录类型图标,右边一列
#define ICON_MEASI_CONTINUE		0		//连续测量
#define ICON_MEASI_LENGTH		1		//长度
#define ICON_MEASI_DELAY			2		//延时
#define ICON_MEASI_LOFT			3		//放样
#define ICON_MEASI_AREA			4		//面积
#define ICON_MEASI_VOLUME		5		//体积
#define ICON_MEASI_GOUGU2		6		//勾股定理2
#define ICON_MEASI_GOUGU3		7		//勾股定理3
#define ICON_MEASI_ANGLE			8		//倾角
#define ICON_MEASI_LEVEL			9		//水平
#define ICON_MEASI_VERTICAL		10		//垂直
#define ICON_MEASI_TRIANGLE		11		//三角

//以下为类型图标,保留用
#define ICON_NULL			71	//清楚

//以下是单色图标
#define ICON_FRACTION		0	//分数10
#define ICON_DIVISOR		1	//分数除号
#define POSITION_NULL		2
#define POSITION_LINE		3

//以下为各种颜色
#define DISPLAY_NULL	0
#define DISPLAY_CURSOR	1
#define DISPLAY_COLOR	2
#define DISPLAY_START	3
#define DISPLAY_WRITE	4
#define DISPLAY_BLUE	5
#define DISPLAY_GREEN	6
#define DISPLAY_RED		7
#define DISPLAY_PURPLE	8	//紫
#define DISPLAY_YELLOW	9	//黄
#define DISPLAY_ORANGE	10	//橙
#define DISPLAY_MAGENTA	11	//粉
#define DISPLAY_CYAN	12		//青
#define DISPLAY_GREY	13		//灰
#define DISPLAY_NAVY	14
#define DISPLAY_OLIVE	15

//以下为主函数
#define FixTaskModule7	fixTaskDisplay
#define FixTimerModule7	fixTimerDisplay	//100mS
#define InitializeModule7	InitializeDisplay
void fixTaskDisplay(void);
void fixTimerDisplay(void);		//mS
void InitializeDisplay(void);

//以下为接口函数

//以下为位变量
#define bBasePoint	vtyBitFlag.Bits.b0		//基准点位置:0=头部;1=底部
#define bBeepOn		vtyBitFlag.Bits.b1		//蜂鸣器
#define bBubble		vtyBitFlag.Bits.b2		//水平气泡

#define bErrorStatus	vtyBitFlag.Bits.b4		//错误状态
#define bLdOn		vtyBitFlag.Bits.b5		//激光已经开

#define bRecordModify		vtyBitFlag.Bits.b8		//记录已经修改
#define bRecordStatus		vtyBitFlag.Bits.b9		//从记录过来

#define bWeakSignal		vtyBitFlag.Bits.b12		//需要切换到内光路?
#define bAdValue		vtyBitFlag.Bits.b13		//马上获得AD值
#define bReadRecord		vtyBitFlag.Bits.b14		//已经读过EEPROM记录
#define bSwitchInternal	vtyBitFlag.Bits.b15		//需要切换到内光路?

#define bDeviation		vtyBitFlag.Bits.b16
#define bGetangle		vtyBitFlag.Bits.b17
#define bAdjruler		vtyBitFlag.Bits.b18

#define bIntDma	vtyMainFlag2.Bits.b20
#define bSpiDma	vtyMainFlag2.Bits.b21
#define bBuzzOn	vtyMainFlag2.Bits.b22	//蜂鸣器

#define bUpdatePrompt	vtyBitFlag.Bits.b26	//更新提示图标
#define bUpdateType	vtyBitFlag.Bits.b27	//更新类型
#define bUpdateBack	vtyBitFlag.Bits.b28	//更新背景
#define bUpdateResult	vtyBitFlag.Bits.b29	//更新结果

/* (C) CopyRight 2006~2012 Mileseey
中国广东省深圳市宝安区西乡街道桃花源科技创新园A栋313~316
深圳迈测科技有限公司
电话0755-8632 9055
End Of File*/
