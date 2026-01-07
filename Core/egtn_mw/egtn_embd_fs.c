/*
 * egtn_ota_bootloader_fs.c
 *
 *  Created on: 2025. 4. 3.
 *      Author: USER
 */

#include <egtn_embd_fs.h>

static struct lfs_config egtn_embd_fs_cfg;
static lfs_t egtn_embd_fs;

static uint8_t egtn_embd_fs_read_buf[256] = {0, };
static uint8_t egtn_embd_fs_prog_buf[256] = {0, };
static uint8_t egtn_embd_fs_lookahead_buf[16] = {0, };



int egtn_embd_fs_externalflash_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
	EGTN_MW_SFLASH_W25qxx_ReadSector((uint8_t*)buffer, block, off, size);
	return 0;
}

int egtn_embd_fs_externalflash_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
	EGTN_MW_SFLASH_W25qxx_WriteSector((uint8_t*)buffer, block, off, size);
	return 0;
}

int egtn_embd_fs_externalflash_erase(const struct lfs_config *c, lfs_block_t block)
{
	EGTN_MW_SFLASH_W25qxx_EraseSector(block);
	return 0;
}

int egtn_embd_fs_externalflash_sync(const struct lfs_config *c)
{
	return 0;
}

void EGTN_EMBD_FS_defaults(void)
{
	egtn_embd_fs_cfg.read = egtn_embd_fs_externalflash_read;
	egtn_embd_fs_cfg.prog = egtn_embd_fs_externalflash_prog;
	egtn_embd_fs_cfg.erase = egtn_embd_fs_externalflash_erase;
	egtn_embd_fs_cfg.sync = egtn_embd_fs_externalflash_sync;

	egtn_embd_fs_cfg.read_size = 256;
	egtn_embd_fs_cfg.prog_size = 256;
	egtn_embd_fs_cfg.block_size = 4096;
	egtn_embd_fs_cfg.block_count = 490;
	egtn_embd_fs_cfg.lookahead_size = 16;
	egtn_embd_fs_cfg.cache_size = 256;
	egtn_embd_fs_cfg.block_cycles = 500;

	egtn_embd_fs_cfg.read_buffer = egtn_embd_fs_read_buf;
	egtn_embd_fs_cfg.prog_buffer = egtn_embd_fs_prog_buf;
	egtn_embd_fs_cfg.lookahead_buffer = egtn_embd_fs_lookahead_buf;
}


int EGTN_EMBD_FS_info(void)
{
	int err = 0;

	EGTN_EMBD_FS_defaults();

    err = lfs_mount(&egtn_embd_fs, &egtn_embd_fs_cfg);
    if (err)
    {
    	return err;
    }

    // get on-disk info
    struct lfs_fsinfo fsinfo;
    err = lfs_fs_stat(&egtn_embd_fs, &fsinfo);
    if (err)
    {
    	return err;
    }

    // get block usage
    lfs_ssize_t in_use = lfs_fs_size(&egtn_embd_fs);
    if (in_use < 0)
    {
        err = in_use;
        return err;
    }

    // print to stdout
    printf("disk_version: lfs%d.%d\r\n",
            0xffff & (fsinfo.disk_version >> 16),
            0xffff & (fsinfo.disk_version >>  0));
    printf("block_size: %d\r\n", egtn_embd_fs_cfg.block_size);
    printf("block_count: %d\r\n", egtn_embd_fs_cfg.block_count);
    printf("  used: %d/%d \r\n", in_use, egtn_embd_fs_cfg.block_count);
    printf("  free: %d/%d \r\n", egtn_embd_fs_cfg.block_count-in_use, egtn_embd_fs_cfg.block_count);
    printf("name_max: %d\n", fsinfo.name_max);
    printf("file_max: %d\n", fsinfo.file_max);
    printf("attr_max: %d\n", fsinfo.attr_max);

    err = lfs_unmount(&egtn_embd_fs);

    return err;
}

int EGTN_EMBD_FS_format(void)
{
    int err = 0;

    EGTN_EMBD_FS_defaults();

    err = lfs_format(&egtn_embd_fs, &egtn_embd_fs_cfg);

    return err;
}

int EGTN_EMBD_FS_mount(void)
{
    return lfs_mount(&egtn_embd_fs, &egtn_embd_fs_cfg);
}

int EGTN_EMBD_FS_unmount(void)
{
	return lfs_unmount(&egtn_embd_fs);
}

int EGTN_EMBD_FS_freeblockcount(lfs_ssize_t * count)
{
    // get the on-disk name_max from littlefs
    struct lfs_fsinfo fsinfo;
    int err = lfs_fs_stat(&egtn_embd_fs, &fsinfo);
    if (err) {
        return err;
    }

    // get the filesystem block usage from littlefs
    lfs_ssize_t in_use = lfs_fs_size(&egtn_embd_fs);
    if (in_use < 0) {
        return in_use;
    }

    //s->f_bsize = egtn_embd_fs_cfg.block_size;
    //s->f_frsize = egtn_embd_fs_cfg.block_size;
    //s->f_blocks = egtn_embd_fs_cfg.block_count;
    //s->f_bfree = egtn_embd_fs_cfg.block_count - in_use;
    //s->f_bavail = egtn_embd_fs_cfg.block_count - in_use;
    //s->f_namemax = fsinfo.name_max;
    *count = egtn_embd_fs_cfg.block_count - in_use;

    return err;
}

lfs_ssize_t EGTN_EMBD_FS_getattr(const char *path, void *buffer) //TODO
{
	lfs_ssize_t res = lfs_getattr(&egtn_embd_fs, path, 0, buffer, 0);

    return res;
}

int EGTN_EMBD_FS_access(const char *path, int mask) //TODO
{
    struct lfs_info info;
    return lfs_stat(&egtn_embd_fs, path, &info);
}

int EGTN_EMBD_FS_mkdir(const char *path)
{
    return lfs_mkdir(&egtn_embd_fs, path);
}

int EGTN_EMBD_FS_opendir(const char *path, lfs_dir_t *pdir)
{
    int err = lfs_dir_open(&egtn_embd_fs, pdir, path);
    return err;
}

int EGTN_EMBD_FS_releasedir(lfs_dir_t *pdir)
{
    int err = lfs_dir_close(&egtn_embd_fs, pdir);
    return err;
}

int EGTN_EMBD_FS_readdir(lfs_dir_t *pdir, void *buf)
{
    struct lfs_info info;

    while (true)
    {
        int err = lfs_dir_read(&egtn_embd_fs, pdir, &info);

        if (err != 1)
        {
            return err;
        }

        printf("FS_readdir : %s\r\n", info.name);
        sprintf((char *)buf, "%s\r\n", info.name);
    }
}

int EGTN_EMBD_FS_rename(const char *from, const char *to)
{
    return lfs_rename(&egtn_embd_fs, from, to);
}

int EGTN_EMBD_FS_remove(const char *path)
{
    return lfs_remove(&egtn_embd_fs, path);
}

int EGTN_EMBD_FS_openfile(lfs_file_t *pfile, const char *path, int flags)
{
    int err = lfs_file_open(&egtn_embd_fs, pfile, path, flags);
    if (err)
    {
        return err;
    }

    return 0;
}

int EGTN_EMBD_FS_closefile(lfs_file_t *pfile)
{
    int err = lfs_file_close(&egtn_embd_fs, pfile);

    return err;
}

#if 0
int lfs_fuse_fgetattr(const char *path, struct stat *s,
        struct fuse_file_info *fi) {
    lfs_file_t *file = (lfs_file_t*)fi->fh;

    lfs_fuse_tostat(s, &(struct lfs_info){
        .size = lfs_file_size(&lfs, file),
        .type = LFS_TYPE_REG,
    });

    return 0;
}
#endif

int EGTN_EMBD_FS_readfile(lfs_file_t *pfile, void *buf, size_t size, lfs_soff_t off)
{
#if 0
    if (lfs_file_tell(&egtn_embd_fs, pfile) != off)
    {
        lfs_soff_t soff = lfs_file_seek(&egtn_embd_fs, pfile, off, LFS_SEEK_SET);
        if (soff < 0)
        {
            return soff;
        }
    }
#endif
    return lfs_file_read(&egtn_embd_fs, pfile, buf, size);
}

int EGTN_EMBD_FS_rewindfile(lfs_file_t *pfile)
{
	lfs_file_rewind(&egtn_embd_fs, pfile);

	return 0;
}

int EGTN_EMBD_FS_writefile(lfs_file_t *pfile, const void *buf, size_t size, lfs_soff_t off)
{
#if 0
    if (lfs_file_tell(&egtn_embd_fs, pfile) != off)
    {
        lfs_soff_t soff = lfs_file_seek(&egtn_embd_fs, pfile, off, LFS_SEEK_SET);
        if (soff < 0)
        {
            return soff;
        }
    }
#endif
    return lfs_file_write(&egtn_embd_fs, pfile, buf, size);
}

#if 0
int lfs_fuse_fsync(const char *path, int isdatasync,
        struct fuse_file_info *fi) {
    lfs_file_t *file = (lfs_file_t*)fi->fh;
    return lfs_file_sync(&lfs, file);
}


int lfs_fuse_flush(const char *path, struct fuse_file_info *fi) {
    lfs_file_t *file = (lfs_file_t*)fi->fh;
    return lfs_file_sync(&lfs, file);
}

int lfs_fuse_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    int err = lfs_fuse_open(path, fi);
    if (err) {
        return err;
    }

    return lfs_fuse_fsync(path, 0, fi);
}

int lfs_fuse_ftruncate(const char *path, off_t size,
        struct fuse_file_info *fi) {
    lfs_file_t *file = (lfs_file_t*)fi->fh;
    return lfs_file_truncate(&lfs, file, size);
}

int lfs_fuse_truncate(const char *path, off_t size) {
    lfs_file_t file;
    int err = lfs_file_open(&lfs, &file, path, LFS_O_WRONLY);
    if (err) {
        return err;
    }

    err = lfs_file_truncate(&lfs, &file, size);
    if (err) {
        return err;
    }

    return lfs_file_close(&lfs, &file);
}
#endif



void EGTN_BOOTLOADER_fs_startup()
{
	EGTN_EMBD_FS_defaults();
}

void EGTN_BOOTLOADER_fs_init()
{
    int err = EGTN_EMBD_FS_mount();

    if(err)
    {
    	printf("@@@EGTN_EMBD_FS : format\r\n");

    	EGTN_EMBD_FS_format();
    	EGTN_EMBD_FS_mount();
    }

}

void EGTN_BOOTLOADER_fs_test()
{
	lfs_dir_t dir_root;
	lfs_dir_t dir_common;
	lfs_file_t file_common_version;
	lfs_file_t file_common_version2;


	char string[40] = {'\0', };
	char filestring[40] = {'\0', };


	EGTN_BOOTLOADER_fs_init();

#if 0
	EGTN_EMBD_FS_mkdir("COMMON");
	EGTN_EMBD_FS_opendir("COMMON", &dir_common);
	EGTN_EMBD_FS_readdir(&dir_common, string);
#endif
	EGTN_EMBD_FS_opendir("/", &dir_root);
	EGTN_EMBD_FS_readdir(&dir_root, string);

	EGTN_EMBD_FS_opendir("/COMMON", &dir_common);
	EGTN_EMBD_FS_readdir(&dir_common, string);

	EGTN_EMBD_FS_openfile(&file_common_version, "/COMMON/version", LFS_O_RDWR | LFS_O_CREAT);
	EGTN_EMBD_FS_readfile(&file_common_version, (char *)filestring, 40, 0);
	printf("/COMMON/version : %s\r\n",filestring);
#if 0
	sprintf(filestring,"%s","123456");

	EGTN_EMBD_FS_rewindfile(&file_common_version);
	EGTN_EMBD_FS_writefile(&file_common_version, (char *)filestring, strlen(filestring), 0);
#endif
	EGTN_EMBD_FS_closefile(&file_common_version);

	EGTN_EMBD_FS_openfile(&file_common_version2, "/version", LFS_O_RDWR | LFS_O_CREAT);
	EGTN_EMBD_FS_readfile(&file_common_version2, (char *)filestring, 40, 0);
	printf("/version : %s\r\n",filestring);
#if 0
	sprintf(filestring,"%s","0103");

	EGTN_EMBD_FS_rewindfile(&file_common_version2);
	EGTN_EMBD_FS_writefile(&file_common_version2, (char *)filestring, strlen(filestring), 0);
#endif
	EGTN_EMBD_FS_closefile(&file_common_version2);







	//EGTN_EMBD_FS_readdir(&dir_common, string);

	//EGTN_EMBD_FS_releasedir(&dir_common);

	lfs_ssize_t fbc = 0;

	EGTN_EMBD_FS_freeblockcount(&fbc);

	printf("fbc : %d\r\n", fbc);

	EGTN_EMBD_FS_unmount();



#if 0
    // read current count
    uint32_t boot_count = 0;
    lfs_file_open(&egtn_embd_fs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&egtn_embd_fs, &file, &boot_count, sizeof(boot_count));

    // update boot count
    boot_count += 1;
    lfs_file_rewind(&egtn_embd_fs, &file);
    lfs_file_write(&egtn_embd_fs, &file, &boot_count, sizeof(boot_count));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&egtn_embd_fs, &file);

    // release any resources we were using
    lfs_unmount(&egtn_embd_fs);

    // print the boot count
    printf("boot_count: %d\r\n", boot_count);
#endif

	while(1);
}
