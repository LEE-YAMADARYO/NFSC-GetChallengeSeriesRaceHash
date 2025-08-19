# NFSC-GetChallengeSeriesRaceHash
此 ASI 插件用于获取 Need for Speed Carbon 挑战赛哈希值

编译完成的 ASI 已在 Release 发布，您可以直接下载并使用
将下载好的 GetChallengeSeriesRaceHash.asi 放置游戏目录下的 Scripts 文件夹中
启动游戏，进入挑战赛界面
此时控制台将会输出所有挑战赛的哈希值

如果您需要单独列出某个挑战赛的哈希值，请依照以下方式查找它的索引：
1. 使用 VltEd 或 OGVI 读取游戏
2. 依次展开至：gameplay>baseelement>activity>progression>race_bin>race_bin_challenge 节点
3. 在 race_bin_challenge 节点中，展开 WorldRaces 字段
4. 左边的字段数即为索引
需要注意的是，第一场挑战赛从字段 [0] 开始

随后修改代码，将

// 需要查找的挑战赛索引
const int TARGET_CHALLENGE_INDEX = 0;

修改为你需要打印的索引，随后重新启用下列被注释的代码

// 打印指定索引的哈希值
// if (BinIndex == TARGET_CHALLENGE_INDEX) {
    // printf("索引为 %d 的挑战赛哈希值: 0x%X ---\n", BinIndex, *EventHash);
// }

编译，随后将 .asi 放置到游戏目录 Scripts 中即可获取指定索引挑战赛的哈希值
