/*
 * egtn_ota_bootloader_fs.h
 *
 *  Created on: 2025. 4. 3.
 *      Author: USER
 */

#ifndef EGTN_APP_INC_EGTN_EMBD_FS_H_
#define EGTN_APP_INC_EGTN_EMBD_FS_H_

#include "main.h"
#include <stdlib.h>
#include <string.h>

#include "egtn_mw_serialflash.h"
#include "egtn_lib_littlefs.h"

void EGTN_EMBD_FS_defaults(void);
int EGTN_EMBD_FS_info(void);
int EGTN_EMBD_FS_format(void);
int EGTN_EMBD_FS_mount(void);
int EGTN_EMBD_FS_unmount(void);
int EGTN_EMBD_FS_freeblockcount(lfs_ssize_t * count);
lfs_ssize_t EGTN_EMBD_FS_getattr(const char *path, void *buffer); //TODO
int EGTN_EMBD_FS_access(const char *path, int mask); //TODO
int EGTN_EMBD_FS_mkdir(const char *path);
int EGTN_EMBD_FS_opendir(const char *path, lfs_dir_t *pdir);
int EGTN_EMBD_FS_releasedir(lfs_dir_t *pdir);
int EGTN_EMBD_FS_readdir(lfs_dir_t *pdir, void *buf);
int EGTN_EMBD_FS_rename(const char *from, const char *to);
int EGTN_EMBD_FS_remove(const char *path);
int EGTN_EMBD_FS_openfile(lfs_file_t *pfile, const char *path, int flags);
int EGTN_EMBD_FS_closefile(lfs_file_t *pfile);
#if 0
int lfs_fuse_fgetattr(const char *path, struct stat *s, struct fuse_file_info *fi);
#endif
int EGTN_EMBD_FS_readfile(lfs_file_t *pfile, void *buf, size_t size, lfs_soff_t off);
int EGTN_EMBD_FS_rewindfile(lfs_file_t *pfile);
int EGTN_EMBD_FS_writefile(lfs_file_t *pfile, const void *buf, size_t size, lfs_soff_t off);
#if 0
int lfs_fuse_fsync(const char *path, int isdatasync,struct fuse_file_info *fi);
int lfs_fuse_flush(const char *path, struct fuse_file_info *fi);
int lfs_fuse_create(const char *path, mode_t mode, struct fuse_file_info *fi);
int lfs_fuse_ftruncate(const char *path, off_t size,struct fuse_file_info *fi);
int lfs_fuse_truncate(const char *path, off_t size);
#endif


//example app function
void EGTN_BOOTLOADER_fs_startup();
void EGTN_BOOTLOADER_fs_init();
void EGTN_BOOTLOADER_fs_test();

#endif /* EGTN_APP_INC_EGTN_EMBD_FS_H_ */
