## **项目规范**

在这个项目中，你将实现一个由写时复制 trie 树支持的键值存储。 trie 是一种高效的有序树数据结构，用于根据给定的键检索值。为了简化解释，我们假设键是变长字符串，但实际上它们可以是任意类型。

树中的每个节点可以有多个子节点，表示不同可能的下一个字符。

你将要实现的键值存储可以存储映射到任何类型值的字符串键。键的值存储在表示该键的最后一个字符的节点(也称为终端节点)中。例如，考虑向 trie 树中插入 k-v 对`("ab"， 1)`和`("ac"， "val")`。

<img src="./%E5%AD%A6%E4%B9%A0%E6%96%87%E4%BB%B6/imgs/image-20240124124247400.png" alt="image-20240124124247400" style="zoom:150%;" />

这两个 key 共享同一个父节点。键 ab 对应的值 1 存储在左子节点中，键 ac 对应的值 val 存储在右子节点中。

## Task #1 - Copy-On-Write Trie

在这个任务中，需要修改`trie .h`和`trie .cpp`来实现一个 copy-on-write trie 。在 copy-on-write trie 中，操作不会直接修改原始 trie 树的节点。相反，对修改后的数据创建新节点，并为新修改的trie树返回一个新根节点。copy-on-write 使我们能够在每次操作之后的任何时间以最小的开销访问trie。考虑在上面的例子中插入`("ad"， 2)`。通过重用原树中的两个子节点，并创建一个新的`Node2`，我们创建了一个新的Node2。(见下图)

![image-20240124124536621](./%E5%AD%A6%E4%B9%A0%E6%96%87%E4%BB%B6/imgs/image-20240124124536621.png)

如果我们插入`("b"， 3)`，我们将创建一个新的根节点，一个新的节点，并重用之前的节点。通过这种方式，我们可以在每次插入操作前后获取trie树的内容。只要我们有根对象(`Trie`类)，我们就可以访问Trie中的数据。(见下图)

![image-20240124124652900](./%E5%AD%A6%E4%B9%A0%E6%96%87%E4%BB%B6/imgs/image-20240124124652900.png)

再举一个例子：如果我们插入`("a"， "abc")`并删除`("ab"， 1)`，我们可以得到下面的 trie 树。注意，父节点可以有值，删除后需要清除所有不必要的节点。

<img src="./%E5%AD%A6%E4%B9%A0%E6%96%87%E4%BB%B6/imgs/image-20240124131335408.png" alt="image-20240124131335408" style="zoom:50%;" />

你的 trie 应该支持3种操作:

- `Get(key)`：获取键对应的值。
- `Put(key, value)`：设置键对应的值。如果键已经存在，则覆盖现有值。请注意，值的类型可能是不可复制的(即`std::unique_ptr<int>`)。这个方法返回一个新的 trie 。
- `Delete(key)`：删除键对应的值。这个方法返回一个新的 trie 。

这些操作都不应该直接在 trie 本身上执行。您应该创建新的 trie 节点，并尽可能重用已有的节点。

要创建新节点，应该使用`TrieNode`类的`Clone`函数。要重用新 trie 树中已经存在的节点，可以复制`std::shared_ptr<TrieNode>`：复制共享指针不会复制底层数据。您不应该在此项目中使用`new`和`delete`手动分配内存。当没有人引用底层对象时，`std::shared_ptr`会释放对象。

有关这些操作的完整规范，请参阅启动器代码中的注释。

## Task #2 - Concurrent Key-Value Store

在你有了一个可以在单线程环境中使用的写时复制trie树之后，为多线程环境实现一个并发的键值存储。在这个任务中，需要修改`trie_store.h`和`trie_store.cpp`。这个键值存储还支持以下3种操作:

- `Get(key)`：返回值
- `Put(key, value)`：没有返回值
- `Delete(key)`：没有返回值

对于原始的Trie类，每次我们修改Trie时，我们都需要获得新的根目录来访问新的内容。但是对于并发的键值存储，`put`和`delete`方法没有返回值。这要求您使用并发原语来同步读写，以便在整个过程中没有数据丢失。

并发的键值存储应该并发地为多个读取器和一个写入器提供服务。也就是说，当有人修改trie时，读取仍然可以在旧的根节点上执行。当有人在读时，仍然可以执行写操作，而无需等待读操作。

此外，如果我们从trie树中获得一个值的引用，我们应该能够访问它，无论我们如何修改trie树。Trie中的`Get`函数只返回一个指针。如果存储该值的`trie`节点已被删除，则指针将悬空。因此，在`TrieStore`中，我们返回一个`ValueGuard`，它存储了对值的引用和对应于trie结构根的TrieNode，这样当我们存储`ValueGuard`时，值可以被访问。

为此，我们在`trie_store.cpp`中提供了`TrieStore::Get`的伪代码。请仔细阅读并思考如何实现`TrieStore::Put`和`TrieStore::Remove`。

## Task #3 - Debugging

在这个任务中，你将学习调试的基本技术。你可以选择任何你喜欢的调试方式，包括但不限于:使用cout和printf，使用cleon / VSCode调试器，使用gdb等。

有关说明，请参阅`trie_debug_test.cpp`。在生成trie结构之后，你需要设置一个断点，并回答一些问题。你需要在`trie_answer.h`中填写答案。

## Task #4 - SQL String Functions

现在是时候深入研究BusTub本身了! 你需要实现`上层`和`下层`SQL函数。这可以通过两步完成:

(1)实现`string_expression.h`中的函数逻辑。

(2)在BusTub中注册函数，以便SQL框架可以在用户执行SQL时调用你的函数，在`plan_func_call.cpp`中。

要测试你的实现，可以使用bustub-shell:

```shell
cd build
make -j`nproc` shell
./bin/bustub-shell
bustub> select upper('AbCd'), lower('AbCd');
ABCD abcd
```

你的实现应该通过所有3个sqllogictest测试用例。

```shell
cd build
make -j`nproc` sqllogictest
./bin/bustub-sqllogictest ../test/sql/p0.01-lower-upper.slt --verbose
./bin/bustub-sqllogictest ../test/sql/p0.02-function-error.slt --verbose
./bin/bustub-sqllogictest ../test/sql/p0.03-string-scan.slt --verbose
```

注意:如果您看到`BufferPoolManager`尚未实现。在运行sqllogictest时，这是正常的，您可以安全地忽略项目0中的这个警告。

# INSTRUCTIONS

## Creating Your Own Project Repository

如果你对下面的`git`概念(例如repository、merge、pull、fork)没有理解，请先花一些时间学习git。

按照说明设置你自己的私有仓库和你自己的开发分支。如果你之前通过GitHub UI创建过分支(点击Fork)，请不要将任何代码推送到你的公共分支仓库在git推送代码之前，请确保仓库是私有的。

如果指导者对代码做了任何更改，您可以通过保持私有存储库连接到CMU-DB主存储库来将更改合并到您的代码中。执行如下命令添加远端源:

```
$ git remote add public https://github.com/cmu-db/bustub.git
```

然后您可以根据需要拉取学期内的最新更改:

```
$ git fetch public
$ git merge public/master
```

## Setting Up Your Development Environment

首先安装BusTub需要的包:

```
# Linux
$ sudo build_support/packages.sh
# macOS
$ build_support/packages.sh
```

有关如何设置不同操作系统环境的更多信息，请参阅README。

要从命令行构建系统，请执行以下命令:

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
$ make -j`nproc`
```

我们建议总是在调试模式下配置CMake。这将使您能够输出调试消息并检查内存泄漏(在下面的小节中有更多关于这方面的内容)。

## Testing

你可以使用我们的测试框架来测试这个任务的各个组成部分。我们使用GTest进行单元测试用例。你可以在命令行中编译并运行每个测试:

```shell
$ cd build
$ make trie_test trie_store_test -j$(nproc)
$ make trie_noncopy_test trie_store_noncopy_test -j$(nproc)
$ ./test/trie_test
$ ./test/trie_noncopy_test
$ ./test/trie_store_test
$ ./test/trie_store_noncopy_test	
```

在这个项目中没有隐藏的测试。将来，在起步代码中提供的测试只是我们将用于评估和评分您的项目的所有测试的子集。您应该自己编写额外的测试用例来检查您的实现的完整功能。

## Formatting

您的代码必须遵循谷歌c++风格指南。我们使用Clang来自动检查源代码的质量。如果你提交的项目没有通过以上任何一项检查，你的项目分数将为零。

执行下面的命令来检查语法。格式目标将自动纠正您的代码。check-lint和check-clang-tidy目标会打印错误，你必须手动修复这些错误，以符合我们的风格指南。

```shell
$ make format
$ make check-lint
$ make check-clang-tidy-p0
```

## Memory Leaks

对于这个项目，我们使用LLVM地址清理程序(ASAN)和泄漏清理程序(LSAN)来检查内存错误。要启用ASAN和LSAN，请在调试模式下配置CMake，并像往常一样运行测试。如果有内存错误，您将看到内存错误报告。注意，macOS只支持地址杀毒，而不支持泄漏杀毒。

在某些情况下，地址清理程序可能会影响调试器的可用性。在这种情况下，你可能需要通过配置CMake项目来禁用所有的过滤工具:

```shell
$ cmake -DCMAKE_BUILD_TYPE=Debug -DBUSTUB_SANITIZER= ..
```

## Development Hints

在调试模式下，可以使用BUSTUB_ASSERT进行断言。请注意，BUSTUB_ASSERT中的语句不会在释放模式下执行。如果在所有情况下都需要断言，请使用BUSTUB_ENSURE。

我们将在发布模式下测试你的实现。要在发布模式下编译你的解决方案	，

```
$ mkdir build_rel && cd build_rel
$ cmake -DCMAKE_BUILD_TYPE=Release ..
```

## GRADING RUBRIC

为了通过这个项目，你必须确保你的代码遵循以下准则:

1. 提交是否成功执行了所有测试用例并生成了正确的答案?
2. 提交执行时是否没有任何内存泄漏?
3. 提交是否遵循代码格式和样式策略?

请注意，我们将使用额外的测试用例对您提交的比我们在未来项目中为您提供的示例测试用例更复杂的测试用例进行评分。

## LATE POLICY

这个项目没有延期的日子。

## SUBMISSION

你需要将你的实现提交给gradscope:

- **https://www.gradescope.com/courses/485657/**

在`build`目录下运行这个命令，它会创建一个名为`project0-submit.zip`的`zip`压缩文件，你可以提交给Gradescope。

```
$ make submit-p0
```

虽然你可以提交你的答案任意多次，但你不应该把gradscope当作你唯一的调试工具。大多数学生在截止日期前提交他们的项目，因此Gradescope将花费更长的时间来处理这些请求。您可能无法及时得到帮助您调试问题的反馈。此外，Gradescope的输出不太可能像调试器(如gdb)的输出那样信息量大，只要你花点时间学习使用它。

## COLLABORATION POLICY

每个学生必须独立完成这项作业。
学生可以与其他人讨论项目的高层次细节。
在小组会议后，学生不允许复制白板上的内容。
学生不允许抄袭他人的答案。
在这个项目中，你可以在谷歌上搜索或者向ChatGPT询问一些高级问题，比如“trie是什么”、“如何使用std::move”。

## 完成

<img src="./%E5%AD%A6%E4%B9%A0%E6%96%87%E4%BB%B6/imgs/image-20240202234633371.png" alt="image-20240202234633371" style="zoom:25%;" />

## 总结

### Test #1

还好主要是要搞清楚智能指针的用法，然后对其进行进行操作即可。

### Test # 2

用 `unique_lock`  加锁。

### Test # 3

处理一下逻辑即可。

