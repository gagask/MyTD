#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QImage>
#include <QRect>
#include <QString>


namespace CONSTANTS{
    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 400;
    const int MARGIN_TOP = 64;

    const QString RIGHT_PATH = ":/rightarrow.png";
    const QString RIGHT_H_PATH = ":/rightarrow_hover.png";
    const QString LEFT_PATH = ":/leftarrow.png";
    const QString LEFT_H_PATH = ":/leftarrow_hover.png";
    const QString HELP_SELECT_TOWER = ":/tower_select.png";
    const QString HELP_UPGRADE = ":/upgrade_menu.png";
    const QString HELP_BUILD_TOWER = ":/tower_builder.png";

    const QString DIRT_TILE = ":/dirt_tile.png";
    const QString GRASS_TILE = ":/grass_tile.png";
    const QString HIGHLIGHT_TILE = ":/tile_highlight.png";

    const QString TOWER_FIRE = ":/fire.png";
    const QString TOWER_ICE = ":/ice.png";
    const QString TOWER_EARTH = ":/rock.png";

    const QString TOWEROPT_H = ":/toweroption_h.png";
    const QString UPGRADE_FIRE_BASE = ":/fire_icon_base.png";
    const QString UPGRADE_ICE_BASE = ":/ice_icon_base.png";
    const QString UPGRADE_EARTH_BASE = ":/earth_icon_base.png";
    const QString UPGRADE_STRENGTH = ":/strength_icon.png";
    const QString UPGRADE_RANGE = ":/target_icon.png";
    const QString UPGRADE_RATE = ":/time_icon.png";

    const int TILE_ROW = 8;
    const int TILE_COL = 8;
    const int PATH_TILE_COUNT = 22;
    const int MAP[TILE_ROW*TILE_COL] = { 0, 0, 0, 0, 0, 0, 1, 0,
                                         0, 7, 6, 5, 4, 3, 2, 0,
                                         0, 8, 0, 0, 0, 0, 0, 0,
                                         0, 9, 0, 0,16,17,18, 0,
                                         0,10, 0, 0,15, 0,19, 0,
                                         0,11,12,13,14, 0,20, 0,
                                         0, 0, 0, 0, 0, 0,21, 0,
                                         0, 0, 0, 0, 0, 0,22, 0};
    const int TOWER_COST = 10;
}

namespace CHARS{
    const QString CHAR_0 = ":/characters/Normal/0.png";
    const QString CHAR_1 = ":/characters/Normal/1.png";
    const QString CHAR_2 = ":/characters/Normal/2.png";
    const QString CHAR_3 = ":/characters/Normal/3.png";
    const QString CHAR_4 = ":/characters/Normal/4.png";
    const QString CHAR_5 = ":/characters/Normal/5.png";
    const QString CHAR_6 = ":/characters/Normal/6.png";
    const QString CHAR_7 = ":/characters/Normal/7.png";
    const QString CHAR_8 = ":/characters/Normal/8.png";
    const QString CHAR_9 = ":/characters/Normal/9.png";
    const QString CHAR_A = ":/characters/Normal/A.png";
    const QString CHAR_B = ":/characters/Normal/B.png";
    const QString CHAR_C = ":/characters/Normal/C.png";
    const QString CHAR_D = ":/characters/Normal/D.png";
    const QString CHAR_E = ":/characters/Normal/E.png";
    const QString CHAR_F = ":/characters/Normal/F.png";
    const QString CHAR_G = ":/characters/Normal/G.png";
    const QString CHAR_H = ":/characters/Normal/H.png";
    const QString CHAR_I = ":/characters/Normal/I.png";
    const QString CHAR_J = ":/characters/Normal/J.png";
    const QString CHAR_K = ":/characters/Normal/K.png";
    const QString CHAR_L = ":/characters/Normal/L.png";
    const QString CHAR_M = ":/characters/Normal/M.png";
    const QString CHAR_N = ":/characters/Normal/N.png";
    const QString CHAR_O = ":/characters/Normal/O.png";
    const QString CHAR_P = ":/characters/Normal/P.png";
    const QString CHAR_Q = ":/characters/Normal/Q.png";
    const QString CHAR_R = ":/characters/Normal/R.png";
    const QString CHAR_S = ":/characters/Normal/S.png";
    const QString CHAR_T = ":/characters/Normal/T.png";
    const QString CHAR_U = ":/characters/Normal/U.png";
    const QString CHAR_V = ":/characters/Normal/V.png";
    const QString CHAR_W = ":/characters/Normal/W.png";
    const QString CHAR_X = ":/characters/Normal/X.png";
    const QString CHAR_Y = ":/characters/Normal/Y.png";
    const QString CHAR_Z = ":/characters/Normal/Z.png";

    const QString CHAR_0_ACT = ":/characters/Active/0.png";
    const QString CHAR_1_ACT = ":/characters/Active/1.png";
    const QString CHAR_2_ACT = ":/characters/Active/2.png";
    const QString CHAR_3_ACT = ":/characters/Active/3.png";
    const QString CHAR_4_ACT = ":/characters/Active/4.png";
    const QString CHAR_5_ACT = ":/characters/Active/5.png";
    const QString CHAR_6_ACT = ":/characters/Active/6.png";
    const QString CHAR_7_ACT = ":/characters/Active/7.png";
    const QString CHAR_8_ACT = ":/characters/Active/8.png";
    const QString CHAR_9_ACT = ":/characters/Active/9.png";
    const QString CHAR_A_ACT = ":/characters/Active/A.png";
    const QString CHAR_B_ACT = ":/characters/Active/B.png";
    const QString CHAR_C_ACT = ":/characters/Active/C.png";
    const QString CHAR_D_ACT = ":/characters/Active/D.png";
    const QString CHAR_E_ACT = ":/characters/Active/E.png";
    const QString CHAR_F_ACT = ":/characters/Active/F.png";
    const QString CHAR_G_ACT = ":/characters/Active/G.png";
    const QString CHAR_H_ACT = ":/characters/Active/H.png";
    const QString CHAR_I_ACT = ":/characters/Active/I.png";
    const QString CHAR_J_ACT = ":/characters/Active/J.png";
    const QString CHAR_K_ACT = ":/characters/Active/K.png";
    const QString CHAR_L_ACT = ":/characters/Active/L.png";
    const QString CHAR_M_ACT = ":/characters/Active/M.png";
    const QString CHAR_N_ACT = ":/characters/Active/N.png";
    const QString CHAR_O_ACT = ":/characters/Active/O.png";
    const QString CHAR_P_ACT = ":/characters/Active/P.png";
    const QString CHAR_Q_ACT = ":/characters/Active/Q.png";
    const QString CHAR_R_ACT = ":/characters/Active/R.png";
    const QString CHAR_S_ACT = ":/characters/Active/S.png";
    const QString CHAR_T_ACT = ":/characters/Active/T.png";
    const QString CHAR_U_ACT = ":/characters/Active/U.png";
    const QString CHAR_V_ACT = ":/characters/Active/V.png";
    const QString CHAR_W_ACT = ":/characters/Active/W.png";
    const QString CHAR_X_ACT = ":/characters/Active/X.png";
    const QString CHAR_Y_ACT = ":/characters/Active/Y.png";
    const QString CHAR_Z_ACT = ":/characters/Active/Z.png";
    const QString CHAR_SPACE = ":/characters/space.png";

    const QString CHAR_0_RED = ":/characters/Red/0.png";
    const QString CHAR_1_RED = ":/characters/Red/1.png";
    const QString CHAR_2_RED = ":/characters/Red/2.png";
    const QString CHAR_3_RED = ":/characters/Red/3.png";
    const QString CHAR_4_RED = ":/characters/Red/4.png";
    const QString CHAR_5_RED = ":/characters/Red/5.png";
    const QString CHAR_6_RED = ":/characters/Red/6.png";
    const QString CHAR_7_RED = ":/characters/Red/7.png";
    const QString CHAR_8_RED = ":/characters/Red/8.png";
    const QString CHAR_9_RED = ":/characters/Red/9.png";
}

class GameObject : public QObject
{
    Q_OBJECT
public:
    GameObject();
    GameObject(QString, qreal=1);
    virtual ~GameObject();

    inline QRect* getRect(){ return rect; }
    inline QImage* getImage() { return image; }
    inline QRect getRectV() const { return *rect; }
    inline QImage getImageV() const { return *image; }

    inline void setImage(QImage i) { image = new QImage(i); }
    inline void setRect(QRect r) { rect = new QRect(r); }
private:
    QImage* image;
    QRect* rect;
};

#endif // GAMEOBJECT_H
