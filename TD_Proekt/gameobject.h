#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QImage>
#include <QRect>
#include <QString>


namespace CONSTANTS{
    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 400;
    const int MARGIN_TOP = 64;

    const QString DIRT_TILE = ":/dirt_tile.png";
    const QString GRASS_TILE = ":/grass_tile.png";
    //const QString HIGHLIGHT_TILE = "D:/Qte/TD_Proekt/tile_highlight.png";

    const QString TOWER_FIRE = ":/fire.png";
    const QString TOWER_ICE = ":/ice.png";
    const QString TOWER_EARTH = ":/rock.png";

    //Ingame GUI
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
    const QString CHAR_0 = ":/characters/normal/0.png";
    const QString CHAR_1 = ":/characters/normal/1.png";
    const QString CHAR_2 = ":/characters/normal/2.png";
    const QString CHAR_3 = ":/characters/normal/3.png";
    const QString CHAR_4 = ":/characters/normal/4.png";
    const QString CHAR_5 = ":/characters/normal/5.png";
    const QString CHAR_6 = ":/characters/normal/6.png";
    const QString CHAR_7 = ":/characters/normal/7.png";
    const QString CHAR_8 = ":/characters/normal/8.png";
    const QString CHAR_9 = ":/characters/normal/9.png";
    const QString CHAR_A = ":/characters/normal/A.png";
    const QString CHAR_B = ":/characters/normal/B.png";
    const QString CHAR_C = ":/characters/normal/C.png";
    const QString CHAR_D = ":/characters/normal/D.png";
    const QString CHAR_E = ":/characters/normal/E.png";
    const QString CHAR_F = ":/characters/normal/F.png";
    const QString CHAR_G = ":/characters/normal/G.png";
    const QString CHAR_H = ":/characters/normal/H.png";
    const QString CHAR_I = ":/characters/normal/I.png";
    const QString CHAR_J = ":/characters/normal/J.png";
    const QString CHAR_K = ":/characters/normal/K.png";
    const QString CHAR_L = ":/characters/normal/L.png";
    const QString CHAR_M = ":/characters/normal/M.png";
    const QString CHAR_N = ":/characters/normal/N.png";
    const QString CHAR_O = ":/characters/normal/O.png";
    const QString CHAR_P = ":/characters/normal/P.png";
    const QString CHAR_Q = ":/characters/normal/Q.png";
    const QString CHAR_R = ":/characters/normal/R.png";
    const QString CHAR_S = ":/characters/normal/S.png";
    const QString CHAR_T = ":/characters/normal/T.png";
    const QString CHAR_U = ":/characters/normal/U.png";
    const QString CHAR_V = ":/characters/normal/V.png";
    const QString CHAR_W = ":/characters/normal/W.png";
    const QString CHAR_X = ":/characters/normal/X.png";
    const QString CHAR_Y = ":/characters/normal/Y.png";
    const QString CHAR_Z = ":/characters/normal/Z.png";

    const QString CHAR_0_ACT = ":/characters/active/0.png";
    const QString CHAR_1_ACT = ":/characters/active/1.png";
    const QString CHAR_2_ACT = ":/characters/active/2.png";
    const QString CHAR_3_ACT = ":/characters/active/3.png";
    const QString CHAR_4_ACT = ":/characters/active/4.png";
    const QString CHAR_5_ACT = ":/characters/active/5.png";
    const QString CHAR_6_ACT = ":/characters/active/6.png";
    const QString CHAR_7_ACT = ":/characters/active/7.png";
    const QString CHAR_8_ACT = ":/characters/active/8.png";
    const QString CHAR_9_ACT = ":/characters/active/9.png";
    const QString CHAR_A_ACT = ":/characters/active/A.png";
    const QString CHAR_B_ACT = ":/characters/active/B.png";
    const QString CHAR_C_ACT = ":/characters/active/C.png";
    const QString CHAR_D_ACT = ":/characters/active/D.png";
    const QString CHAR_E_ACT = ":/characters/active/E.png";
    const QString CHAR_F_ACT = ":/characters/active/F.png";
    const QString CHAR_G_ACT = ":/characters/active/G.png";
    const QString CHAR_H_ACT = ":/characters/active/H.png";
    const QString CHAR_I_ACT = ":/characters/active/I.png";
    const QString CHAR_J_ACT = ":/characters/active/J.png";
    const QString CHAR_K_ACT = ":/characters/active/K.png";
    const QString CHAR_L_ACT = ":/characters/active/L.png";
    const QString CHAR_M_ACT = ":/characters/active/M.png";
    const QString CHAR_N_ACT = ":/characters/active/N.png";
    const QString CHAR_O_ACT = ":/characters/active/O.png";
    const QString CHAR_P_ACT = ":/characters/active/P.png";
    const QString CHAR_Q_ACT = ":/characters/active/Q.png";
    const QString CHAR_R_ACT = ":/characters/active/R.png";
    const QString CHAR_S_ACT = ":/characters/active/S.png";
    const QString CHAR_T_ACT = ":/characters/active/T.png";
    const QString CHAR_U_ACT = ":/characters/active/U.png";
    const QString CHAR_V_ACT = ":/characters/active/V.png";
    const QString CHAR_W_ACT = ":/characters/active/W.png";
    const QString CHAR_X_ACT = ":/characters/active/X.png";
    const QString CHAR_Y_ACT = ":/characters/active/Y.png";
    const QString CHAR_Z_ACT = ":/characters/active/Z.png";
    const QString CHAR_SPACE = ":/characters/space.png";

    const QString CHAR_0_RED = ":/characters/red/0.png";
    const QString CHAR_1_RED = ":/characters/red/1.png";
    const QString CHAR_2_RED = ":/characters/red/2.png";
    const QString CHAR_3_RED = ":/characters/red/3.png";
    const QString CHAR_4_RED = ":/characters/red/4.png";
    const QString CHAR_5_RED = ":/characters/red/5.png";
    const QString CHAR_6_RED = ":/characters/red/6.png";
    const QString CHAR_7_RED = ":/characters/red/7.png";
    const QString CHAR_8_RED = ":/characters/red/8.png";
    const QString CHAR_9_RED = ":/characters/red/9.png";
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

    //rect and image setters
    inline void setImage(QImage i) { image = new QImage(i); }
    inline void setRect(QRect r) { rect = new QRect(r); }

private:
    QImage* image;
    QRect* rect;
};

#endif // GAMEOBJECT_H
