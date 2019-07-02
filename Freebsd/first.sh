zfs set compression=gzip zroot/tmp
zfs get all zroot/tmp | grep compress


zfs create zroot/test

echo aaaa > a
echo bbbb > b
zfs snapshot zroot/test@1

rm a
zfs snapshot zroot/test@2

zfs list -t snapshot

zfs diff zroot/test@1 zroot/test@2

zfs rollback zroot/test@1