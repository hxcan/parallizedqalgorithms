#ifndef GAMETYPE_H
#define GAMETYPE_H

/*!
 *@brief 这是关于游戏类型的命名空间。
 */
namespace GameType
{
/*!
 * \brief The GameType enum 游戏分类。
 */
enum GameType
{
    BigNetworkGame=0, //!<大型网游。
    WebGame=1, //!<网页游戏。
    BoardGame=2, //!<棋牌游戏。
    LeisureGame=3 //!<休闲娱乐游戏。
}; //enum GameType
} //namespace GameType

#endif // GAMETYPE_H
