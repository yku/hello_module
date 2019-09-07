# hello_module

- 下記のメッセージが出る場合は、MODULE_LICENSE("GPL")を追加する
- 下記のシンボルはGPLライセンスのためドライバ側もGPLでないと見えない

```
[ 1560.239247] hello: Unknown symbol kernel_kobj (err 0)
[ 1560.239307] hello: Unknown symbol sysfs_create_group (err 0)
[ 1560.239356] hello: Unknown symbol kobject_create_and_add (err 0)
```
- kernel_kobjの子供として作成したため、/sys/kernel以下に配置される

```
# cat /sys/kernel/hello_mod/echo
Hello World
# cat /sys/kernel/hello_mod/version
v0.1
```

- attribute_groupの.nameに値を設定するとその配下にパラメータが作成される

```
static struct attribute_group hello_attr_group = { 
    .name = "hello_child",
    .attrs = hello_sysfs_attrs,
};


# ls /sys/kernel/hello_mod/hello_child/
echo  version
```
