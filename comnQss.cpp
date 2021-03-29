#include "comnQss.h"

#define GET_STR(x) #x

QString qssBtnInLoginWel = "QPushButton{font-size:14px;text-align:center;}\
							QPushButton:enabled{color: white; border: none;border-style:none; background: rgb(51, 146, 255;)}\
                                               :enabled:hover{background: rgb(18, 120, 237)}\
                                               :enabled:pressed{background: rgb(18, 110, 215)}\
                                               :!enabled{color: white;border: none;background: rgb(186, 186, 186)}\
											    QPushButton:focus{outline: none;}";
QString qssBtnOrange = "QPushButton{font-size:14px;}\
						   	QPushButton:enabled{color: white; border: none;border-style:none; background: rgb(255, 109, 58;)}\
							:enabled:hover{background: rgb(237, 80, 25)}\
							:enabled:pressed{background: rgb(243, 103, 53)}\
							:!enabled{color: white;border: none;background: rgb(186, 186, 186)}\
							QPushButton:focus{outline: none;}";

QString qssBtnOrange12px = "QPushButton{font-size:12px;text-align:center;}\
					   	QPushButton:enabled{color: white; border: none;border-style:none; background: rgb(255, 109, 58;)}\
						:enabled:hover{background: rgb(237, 80, 25)}\
						:enabled:pressed{background: rgb(243, 103, 53)}\
						:!enabled{color: white;border: none;background: rgb(186, 186, 186)}\
																																																																																																																																							QPushButton:focus{outline: none;}";

QString qssLeInLoginWel = "QLineEdit{padding-bottom: 10px;padding-right: 20px;background: rgb(0, 0, 0, 0);border: 0px solid rgb(0, 0, 0, 0); border-bottom-width: 1px; border-bottom-color: rgb(184, 182, 180)}";
QString qssLeInLoginWelError = "QLineEdit{padding-bottom: 10px;padding-right: 20px;background: rgb(0, 0, 0, 0);border: 0px solid rgb(0, 0, 0, 0); border-bottom-width: 1px; border-bottom-color: red}";

QString qssLeLoginErrTip = "QLabel{color: red; min-width: 251px; max-width: 251px; min-height: 28px; max-height: 28px; font-size:12px;}";

QString qssBorderBtn = "QPushButton:enabled{font:14px;color:rgb(88,91,95); border: 1px solid rgb(191,199,208); background: rgb(255, 255, 255)}\
					   	:enabled:hover{font:14px;color:rgb(51,146,255);border:1px solid rgb(51,146,255);background: rgb(255, 255, 255)}\
						:enabled:pressed{font:14px;color:rgb(19,110,215);border:1px solid rgb(19,110,215);background: rgb(255, 255, 255)}\
						:!enabled{font:14px;color:rgb(176,177,178);border:1px solid rgb(236,238,241);background: rgb(255, 255, 255)}\
						QPushButton:focus{outline: none;}";

QString qssBorderBtn12px = "QPushButton:enabled{font:12px;color:rgb(88,91,95); border: 1px solid rgb(191,199,208); background: rgb(255, 255, 255)}\
					   	:enabled:hover{font:12px;color:rgb(51,146,255);border:1px solid rgb(51,146,255);background: rgb(255, 255, 255)}\
						:enabled:pressed{font:12px;color:rgb(19,110,215);border:1px solid rgb(19,110,215);background: rgb(255, 255, 255)}\
						:!enabled{font:12px;color:rgb(176,177,178);border:1px solid rgb(236,238,241);background: rgb(255, 255, 255)}\
						QPushButton:focus{outline: none;}";

QString qssBlueBorderBtn12px = "QPushButton:enabled{font:12px;color:rgb(35,127,255); border: 1px solid rgb(35,127,255); background: rgb(255, 255, 255)}\
						   :enabled:hover{font:12px;color:rgb(29,103,205);border:1px solid rgb(29,103,205);background: rgb(255, 255, 255)}\
						   :enabled:pressed{font:12px;color:rgb(29,103,205);border:1px solid rgb(29,103,205);background: rgb(235, 243, 255)}\
						   :!enabled{font:12px;color:rgb(176,177,178);border:1px solid rgb(236,238,241);background: rgb(255, 255, 255)}\
						    QPushButton:focus{outline: none;}";


QString qssMenu = "QMenu{background-color:white; border: 1px solid rgb(156, 174, 201); font-size:12px;}\
                   ::item{padding-left: 10px;padding-right: 10px;padding-top:5px;padding-bottom:5px; background-color:white }\
				   ::item:selected{background-color: rgb(227, 238, 251); color:rgb(51, 146, 255); }\
				   QMenu::icon{position:absolute;left:1px;}";


QString strCheckBoxQss = "QCheckBox{font-size: 12px;}\
						 QCheckBox::indicator{width:12px; height:12px; font-size: 12px;}\
				         QCheckBox::indicator:unchecked{border-image:url(:/res/checkbox/icon_Checkbox_not_normal.png);}\
						 QCheckBox::indicator:unchecked:hover{border-image:url(:/res/checkbox/icon_Checkbox_not_hover.png);}\
						 QCheckBox::indicator:checked{border-image:url(:/res/checkbox/icon_Chekbox_all_normal.png);}\
					     QCheckBox::indicator:checked:hover{border-image:url(:/res/checkbox/icon_Chekbox_all_hover.png);}\
						 QCheckBox{color:rgb(46,46,46)}";