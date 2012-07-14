/*
��Ŀ:		�������
��д:		��̶�		SunJD99@Yahoo.com.cn
ģ������:	TFT��ʾ������
�ļ���:	tft.global.h
MCU:	STM32F10X		Ŀǰ��STM32F101R8/STM32F103RB
��ʼʱ��:	2011-7-13 10:13:07
*/

//����Ϊ�궨��

//����Ϊ����
//��������ʾ�ַ��й�
#define LINE_MIDDLE_HZ	(220 / 21)		//�к���������
#define LINE_SMALL_HZ	(220 / 14)		//С����������
#define LINE_TINY_ASCII	(220 / 10)		//С����������
#define LINE_NUMBER	4			//����������
#define QUANTITY_MIDDLE_HZ	(176 / 20)	//ÿ���к�������,
#define QUANTITY_SMALL_HZ	(176 / 12)		//ÿ��С��������
#define QUANTITY_NUMBER	6		//ÿ�����ַ�����
#define QUANTITY_MIDDLE_ASCII	(176 / 10)		//ÿ�����ַ�����
#define QUANTITY_SMALL_ASCII	(176 / 10)		//ÿ��С�ַ�����
#define QUANTITY_TINY_ASCII	28		//(176 / 6)		//ÿ��΢�ַ�����

//��������ʾ�ַ�

//����Ϊ�����FLASH�����ͼ��,Ŀǰ����ͼƬ������FLASH����
//����Ϊ��ʾͼ��,���һ��
#define PROMPT_LENGTH_0_U			0	//����0,ѡǰ
#define PROMPT_LENGTH_0_S			1	//����0,ѡ��
#define PROMPT_LENGTH_1_U			2	//����1,ѡǰ
#define PROMPT_LENGTH_1_S			3	//����1,ѡ��
#define PROMPT_CONTINUE				4	//����
#define PROMPT_CONTINUE_MAX_E		5	//����,���,Ӣ��
#define PROMPT_CONTINUE_MIN_E		6	//����,��С,Ӣ��
#define PROMPT_CONTINUE_MAX_C		7	//����,���,����
#define PROMPT_CONTINUE_MIN_C		8	//����,��С,����
#define PROMPT_AREA_X				9	//���,��
#define PROMPT_AREA_X_U				10	//���,��,ѡǰ
#define PROMPT_AREA_X_S				11	//���,��,ѡ��
#define PROMPT_AREA_Y				12	//���,��
#define PROMPT_AREA_Y_U				13	//���,��,ѡǰ
#define PROMPT_AREA_Y_S				14	//���,��,ѡ��
#define PROMPT_AREA					15	//���
#define PROMPT_AREA_PERIMETER		16	//���,�ܳ�
#define PROMPT_VOL_Y				17	//���,��
#define PROMPT_VOL_Y_U				18	//���,��,ѡǰ
#define PROMPT_VOL_Y_S				19	//���,��,ѡ��
#define PROMPT_VOL_FLOOR			20	//���,�����
#define PROMPT_VOL_FLOOR_S			21	//���,�����,ѡ��
#define PROMPT_VOL_PERIMETER		22	//���,���ܳ�
#define PROMPT_VOL_PERIMETER_S		23	//���,���ܳ�,ѡ��
#define PROMPT_VOL_Z				24	//���,��
#define PROMPT_VOL_Z_U				25	//���,��,ѡǰ
#define PROMPT_VOL_Z_S				26	//���,��,ѡ��
#define PROMPT_VOL_X				27	//���,��
#define PROMPT_VOL_X_U				28	//���,��,ѡǰ
#define PROMPT_VOL_X_S				29	//���,��,ѡ��
#define PROMPT_VOL_WALL				30	//���,ǽ�����
#define PROMPT_VOL_WALL_S				31	//���,ǽ�����,ѡ��
#define PROMPT_VOLUME				32	//���
#define PROMPT_GOUGU2				33	//����2
#define PROMPT_GOUGU2_AGL			34	//����2,�н�
#define PROMPT_GOUGU2_LVL			35	//����2,ˮƽ��
#define PROMPT_GOUGU2_LVL_U			36	//����2,ˮƽ��,ѡǰ
#define PROMPT_GOUGU2_LVL_S			37	//����2,ˮƽ��,ѡ��
#define PROMPT_GOUGU2_SLP			38	//����2,б��
#define PROMPT_GOUGU2_SLP_U			39	//����2,б��,ѡǰ
#define PROMPT_GOUGU2_SLP_S			40	//����2,б��,ѡ��
#define PROMPT_GOUGU3				41	//����3
#define PROMPT_GOUGU3_ANGLE			42	//����3,�н�
#define PROMPT_GOUGU3_ANGLE_S		43	//����3,�н�,ѡ��
#define PROMPT_GOUGU3_VET1			44	//����3,�ϴ�ֱ��
#define PROMPT_GOUGU3_VET1_S		45	//����3,�ϴ�ֱ��,ѡ��
#define PROMPT_GOUGU3_SL1			46	//����3,��б��
#define PROMPT_GOUGU3_SL1_U			47	//����3,��б��,ѡǰ
#define PROMPT_GOUGU3_SL1_S			48	//����3,��б��,ѡ��
#define PROMPT_GOUGU3_LVL			49	//����3,ˮƽ��
#define PROMPT_GOUGU3_LVL_U			50	//����3,ˮƽ��,ѡǰ
#define PROMPT_GOUGU3_LVL_S			51	//����3,ˮƽ��,ѡ��
#define PROMPT_GOUGU3_VET2			52	//����3,�´�ֱ��
#define PROMPT_GOUGU3_VET2_S		53	//����3,�´�ֱ��,ѡ��
#define PROMPT_GOUGU3_SL2			54	//����3,��б��
#define PROMPT_GOUGU3_SL2_U			55	//����3,��б��,ѡǰ
#define PROMPT_GOUGU3_SL2_S			56	//����3,��б��,ѡ��
#define PROMPT_ANGLE				57	//�Ƕ�
#define PROMPT_ANGLE_ANGLE			58	//�Ƕ�,�Ƕ�
#define PROMPT_ANGLE_SLOP			59	//�Ƕ�,б��
#define PROMPT_ANGLE_SLOP_U			60	//�Ƕ�,б��,ѡǰ
#define PROMPT_ANGLE_SLOP_S			61	//�Ƕ�,б��,ѡ��
#define PROMPT_LEVEL_VET			62	//ˮƽ,��ֱ��
#define PROMPT_LEVEL_AGL			63	//ˮƽ,�н�
#define PROMPT_LEVEL				64	//ˮƽ
#define PROMPT_LEVEL_SLP			65	//ˮƽ,б��
#define PROMPT_LEVEL_SLP_U			66	//ˮƽ,б��,ѡǰ
#define PROMPT_LEVEL_SLP_S			67	//ˮƽ,б��,ѡ��
#define PROMPT_VERTICAL				68	//��ֱ
#define PROMPT_VERTICAL_ANGLE		69	//��ֱ,�н�
#define PROMPT_VERTICAL_ANGLE_S		70	//��ֱ,�н�,ѡ��
#define PROMPT_VERTICAL_VET1		71	//��ֱ,�ϴ�ֱ��
#define PROMPT_VERTICAL_VET1_S		72	//��ֱ,�ϴ�ֱ��,ѡ��
#define PROMPT_VERTICAL_SLP1_U		73	//��ֱ,��б��,ѡǰ
#define PROMPT_VERTICAL_SLP1_S		74	//��ֱ,��б��,ѡ��
#define PROMPT_VERTICAL_SLP1		75	//��ֱ,��б��
#define PROMPT_VERTICAL_VET2		76	//��ֱ,�´�ֱ��
#define PROMPT_VERTICAL_VET2_S		77	//��ֱ,�´�ֱ��,ѡ��
#define PROMPT_VERTICAL_SLP2_U		78	//��ֱ,��б��,ѡǰ
#define PROMPT_VERTICAL_SLP2_S		79	//��ֱ,��б��,ѡ��
#define PROMPT_VERTICAL_SLP2		80	//��ֱ,��б��
#define PROMPT_TRIANGLE_B			81	//����,�ڶ���
#define PROMPT_TRIANGLE_B_U			82	//����,�ڶ���,ѡǰ
#define PROMPT_TRIANGLE_B_S			83	//����,�ڶ���,ѡ��
#define PROMPT_TRIANGLE_C			84	//����,������
#define PROMPT_TRIANGLE_C_U			85	//����,������,ѡǰ
#define PROMPT_TRIANGLE_C_S			86	//����,������,ѡ��
#define PROMPT_TRIANGLE_A			87	//����,��һ��
#define PROMPT_TRIANGLE_A_U			88	//����,��һ��,ѡǰ
#define PROMPT_TRIANGLE_A_S			89	//����,��һ��,ѡ��
#define PROMPT_TRIANGLE				90	//����
#define PROMPT_TRIANGLE_PERMR		91	//����,�����ܳ�
#define PROMPT_TRIANGLE_PERMR_S		92	//����,�����ܳ�,ѡ��
#define PROMPT_TRIANGLE_ANGLE		93	//����,һ���߼н�
#define PROMPT_TRIANGLE_ANGLE_S		94	//����,һ���߼н�,ѡ��
#define PROMPT_LOFT_BIAS			95	//����,ƫ��
#define PROMPT_LOFT					96	//����
#define PROMPT_DELAY				97	//��ʱ
#define PROMPT_MATH_EQUAL			98	//����,��
#define PROMPT_MATH_PLUS			99	//����,��
#define PROMPT_MATH_MINUS			100	//����,��
#define PROMPT_MENU_TOOLS_U			101	//�˵�,����,ѡ��
#define PROMPT_MENU_TOOLS			102	//�˵�,����
#define PROMPT_MENU_TOOLS_S			103	//�˵�,����,ѡ��
#define PROMPT_MENU_SET_U			104	//�˵�,����,ѡ��
#define PROMPT_MENU_SET				105	//�˵�,����
#define PROMPT_MENU_SET_S			106	//�˵�,����,ѡ��
#define PROMPT_MENU_PERSON_U		107	//�˵�,����,ѡ��
#define PROMPT_MENU_PERSON			108	//�˵�,����
#define PROMPT_MENU_PERSON_S		109	//�˵�,����,ѡ��
#define PROMPT_MENU_OTHERS_U		110	//�˵�,����,ѡ��
#define PROMPT_MENU_OTHERS			111	//�˵�,����
#define PROMPT_MENU_OTHERS_S		112	//�˵�,����,ѡ��
#define PROMPT_RECORD_ALL_S			113	//��¼,����,ѡ��
#define PROMPT_RECORD_ALL			114	//��¼,����
#define PROMPT_RECORD_ALL_U			115	//��¼,����,ѡ��
#define PROMPT_RECORD_DISTANCE_S	116	//��¼,����,ѡ��
#define PROMPT_RECORD_DISTANCE		117	//��¼,����
#define PROMPT_RECORD_DISTANCE_U	118	//��¼,����,ѡ��
#define PROMPT_RECORD_AREA_S		119	//��¼,���,ѡ��
#define PROMPT_RECORD_AREA			120	//��¼,���
#define PROMPT_RECORD_AREA_U		121	//��¼,���,ѡ��
#define PROMPT_RECORD_ANGLE_S		122	//��¼,�Ƕ�,ѡ��
#define PROMPT_RECORD_ANGLE			123	//��¼,�Ƕ�
#define PROMPT_RECORD_ANGLE_U		124	//��¼,�Ƕ�,ѡ��
#define PROMPT_RECORD_LOCK_S		125	//��¼,����,ѡ��
#define PROMPT_RECORD_LOCK			126	//��¼,����
#define PROMPT_RECORD_LOCK_U		127	//��¼,����,ѡ��
#define PROMPT_NULL					128	//��

//����Ϊ��ʾ����,���һ��
#define ICON_PROMPT_UP_N	0
#define ICON_PROMPT_UP		1
#define ICON_PROMPT_DOWN_N	2
#define ICON_PROMPT_DOWN	3

//����Ϊ��������,�ϱ�һ��
#define ICON_TYPE_LEFT_N	0
#define ICON_TYPE_LEFT		1
#define ICON_TYPE_RIGHT_N	2
#define ICON_TYPE_RIGHT		3

//����Ϊ����ͼ��,�ϱ�һ��
#define TYPE_CONTINUE			0	//��������
#define TYPE_DELAY				1	//��ʱ����
#define TYPE_LOFT				2	//��������
#define TYPE_LENGTH				3	//����ͼ��
#define TYPE_AREA_RIGHT			4	//���
#define TYPE_AREA_MIDDLE		5	//���
#define TYPE_AREA_LEFT			6	//���
#define TYPE_VOLUME_RIGHT		7	//���
#define TYPE_VOLUME_MIDDLE		8	//���
#define TYPE_VOLUME_LEFT		9	//���
#define TYPE_G2_RIGHT			10	//����2
#define TYPE_G2_MIDDLE			11	//����2
#define TYPE_G2_LEFT			12	//����2
#define TYPE_G3_RIGHT			13	//����3
#define TYPE_G3_MIDDLE			14	//����3
#define TYPE_G3_LEFT			15	//����3
#define TYPE_ANGLE_RIGHT		16	//���
#define TYPE_ANGLE_MIDDLE		17	//���
#define TYPE_ANGLE_LEFT			18	//���
#define TYPE_LEVEL_RIGHT		19	//ˮƽ
#define TYPE_LEVEL_MIDDLE		20	//ˮƽ
#define TYPE_LEVEL_LEFT			21	//ˮƽ
#define TYPE_VERTICAL_RIGHT		22	//��ֱ
#define TYPE_VERTICAL_MIDDLE	23	//��ֱ
#define TYPE_VERTICAL_LEFT		24	//��ֱ
#define TYPE_TRIANGLE_RIGHT		25	//����
#define TYPE_TRIANGLE_MIDDLE	26	//����
#define TYPE_TRIANGLE_LEFT		27	//����

//����Ϊ������ʾͼ��
#define ICON_LOFT_FIXEDLY	0
#define ICON_LOFT_BACKWARD	1
#define ICON_LOFT_FORWARD	2

//����Ϊ����ͼ��
#define SYMBOL_DEGREE_PLUS		0	//�Ƕ�+
#define SYMBOL_DEGREE_MINUS		1	//�Ƕ�-
#define SYMBOL_PLUS		2
#define SYMBOL_MINUS		3

//����Ϊ����ͼ��
#define OTHER_ENGINEER		0	//3����
#define OTHER_Y_BUBBLE		1	//10 ��ֱ ����
#define OTHER_Y_GRADIENTER	2	//10 ��ֱ ˮ��
#define OTHER_X_BUBBLE		3	//10 ˮƽ ����
#define OTHER_X_GRADIENTER	4	//10 ˮƽ ˮ��
#define OTHER_45_BUBBLE		5	//10 б�� ����
#define OTHER_45_GRADIENTER	6	//10 б�� ˮ��
#define OTHER_OK			7	//ok
#define OTHER_OK_BUTTON		8	//OK ��ť
#define OTHER_USB			9	//USB
#define OTHER_MENU_RIGHT_U	10	//�˵� �� ѡǰ
#define OTHER_MENU_RIGHT_S	11	//�˵� �� ѡ��
#define OTHER_ERROR_0		12	//������ ͼ��
#define OTHER_ERROR_1		13	//�������� ͼ��
#define OTHER_TOOLS_USB_0	14	//���� ���ݵ���02 �м�ͼ��
#define OTHER_TOOLS_USB_1	15	//���� ���ݵ���03 �м�ͼ��
#define OTHER_TOOLS_USB_2	16	//���� ���ݵ���04 �м�ͼ��
#define OTHER_RECORD_U		17	//��¼ ���� ѡǰ
#define OTHER_RECORD_S		18	//��¼ ���� ѡ��
#define OTHER_RECORD_BACK	19	//��¼ �²� ����ͼ
#define OTHER_TYPE_BACK		20	//���Ͳ��� ��ͼ
#define OTHER_BRIGHT_0		21	//���� �ո�
#define OTHER_BRIGHT_1		22	//���� ����
#define OTHER_OPTION_U		23	//ť ѡǰ
#define OTHER_OPTION_S		24	//ť ѡ��
#define OTHER_DEVICE_0		25	//�豸ͼ��
#define OTHER_DEVICE_1		26	//�豸��תͼ��
#define OTHER_BUBBLE_0		27	//ˮƽ�� ����
#define OTHER_BUBBLE_1		28	//ˮƽ�� ����
#define OTHER_THERMOMETER_0	29	//�¶ȼ� 0
#define OTHER_THERMOMETER_1	30	//�¶ȼ� 1
#define OTHER_THERMOMETER_2	31	//�¶ȼ� 2
#define OTHER_THERMOMETER_3	32	//�¶ȼ��� ��ͼ
#define OTHER_THERMOMETER_4	33	//�¶ȼ��� ��ͼ
#define OTHER_PROMPT_BACK	34	//�²���� ��ͼ
#define OTHER_LOCK			35	//��Ҫ���ݱ�־
#define OTHER_TITLE_BACK	36	//״̬�� ��ͼ

//����Ϊ��¼����ͼ��,�ұ�һ��
#define ICON_MEASI_CONTINUE		0		//��������
#define ICON_MEASI_LENGTH		1		//����
#define ICON_MEASI_DELAY			2		//��ʱ
#define ICON_MEASI_LOFT			3		//����
#define ICON_MEASI_AREA			4		//���
#define ICON_MEASI_VOLUME		5		//���
#define ICON_MEASI_GOUGU2		6		//���ɶ���2
#define ICON_MEASI_GOUGU3		7		//���ɶ���3
#define ICON_MEASI_ANGLE			8		//���
#define ICON_MEASI_LEVEL			9		//ˮƽ
#define ICON_MEASI_VERTICAL		10		//��ֱ
#define ICON_MEASI_TRIANGLE		11		//����

//����Ϊ����ͼ��,������
#define ICON_NULL			71	//���

//�����ǵ�ɫͼ��
#define ICON_FRACTION		0	//����10
#define ICON_DIVISOR		1	//��������
#define POSITION_NULL		2
#define POSITION_LINE		3

//����Ϊ������ɫ
#define DISPLAY_NULL	0
#define DISPLAY_CURSOR	1
#define DISPLAY_COLOR	2
#define DISPLAY_START	3
#define DISPLAY_WRITE	4
#define DISPLAY_BLUE	5
#define DISPLAY_GREEN	6
#define DISPLAY_RED		7
#define DISPLAY_PURPLE	8	//��
#define DISPLAY_YELLOW	9	//��
#define DISPLAY_ORANGE	10	//��
#define DISPLAY_MAGENTA	11	//��
#define DISPLAY_CYAN	12		//��
#define DISPLAY_GREY	13		//��
#define DISPLAY_NAVY	14
#define DISPLAY_OLIVE	15

//����Ϊ������
#define FixTaskModule7	fixTaskDisplay
#define FixTimerModule7	fixTimerDisplay	//100mS
#define InitializeModule7	InitializeDisplay
void fixTaskDisplay(void);
void fixTimerDisplay(void);		//mS
void InitializeDisplay(void);

//����Ϊ�ӿں���

//����Ϊλ����
#define bBasePoint	vtyBitFlag.Bits.b0		//��׼��λ��:0=ͷ��;1=�ײ�
#define bBeepOn		vtyBitFlag.Bits.b1		//������
#define bBubble		vtyBitFlag.Bits.b2		//ˮƽ����

#define bErrorStatus	vtyBitFlag.Bits.b4		//����״̬
#define bLdOn		vtyBitFlag.Bits.b5		//�����Ѿ���

#define bRecordModify		vtyBitFlag.Bits.b8		//��¼�Ѿ��޸�
#define bRecordStatus		vtyBitFlag.Bits.b9		//�Ӽ�¼����

#define bWeakSignal		vtyBitFlag.Bits.b12		//��Ҫ�л����ڹ�·?
#define bAdValue		vtyBitFlag.Bits.b13		//���ϻ��ADֵ
#define bReadRecord		vtyBitFlag.Bits.b14		//�Ѿ�����EEPROM��¼
#define bSwitchInternal	vtyBitFlag.Bits.b15		//��Ҫ�л����ڹ�·?

#define bDeviation		vtyBitFlag.Bits.b16
#define bGetangle		vtyBitFlag.Bits.b17
#define bAdjruler		vtyBitFlag.Bits.b18

#define bIntDma	vtyMainFlag2.Bits.b20
#define bSpiDma	vtyMainFlag2.Bits.b21
#define bBuzzOn	vtyMainFlag2.Bits.b22	//������

#define bUpdatePrompt	vtyBitFlag.Bits.b26	//������ʾͼ��
#define bUpdateType	vtyBitFlag.Bits.b27	//��������
#define bUpdateBack	vtyBitFlag.Bits.b28	//���±���
#define bUpdateResult	vtyBitFlag.Bits.b29	//���½��

/* (C) CopyRight 2006~2012 Mileseey
�й��㶫ʡ�����б���������ֵ��һ�Դ�Ƽ�����԰A��313~316
��������Ƽ����޹�˾
�绰0755-8632 9055
End Of File*/
