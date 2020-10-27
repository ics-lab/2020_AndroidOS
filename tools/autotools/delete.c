/*
 ** tsk_recover
 ** The Sleuth Kit 
 **
 ** Brian Carrier [carrier <at> sleuthkit [dot] org]
 ** Copyright (c) 2010-2011 Brian Carrier.  All Rights reserved
 **
 ** This software is distributed under the Common Public License 1.0
 **
 */

#include "tsk/tsk_tools_i.h"
#include <locale.h>
#include <sys/stat.h>
#include <errno.h>
#include "tsk/fs/tsk_ext2fs.h"

static TSK_TCHAR *progname;

int main(int argc, char **argv1)
{
    TSK_IMG_TYPE_ENUM imgtype = TSK_IMG_TYPE_DETECT;
    TSK_FS_TYPE_ENUM fstype = TSK_FS_TYPE_DETECT;
    int ch;
    TSK_TCHAR **argv;
    unsigned int ssize = 0;
    TSK_OFF_T soffset = 0;
    TSK_TCHAR *cp;
    TSK_FS_DIR_WALK_FLAG_ENUM walkflag = TSK_FS_DIR_WALK_FLAG_UNALLOC;
    TSK_INUM_T dirInum = 0;

    TSK_IMG_INFO * m_img_info;

    argv = (TSK_TCHAR **) argv1;

    m_img_info = tsk_img_open(1, &argv[1], imgtype, ssize);
    
    if (m_img_info == NULL) 
    {
        fprintf(stderr, "img can not open\n");
        return 0;
    }
    TSK_FS_INFO *fs_info;

    if ((fs_info = tsk_fs_open_img(m_img_info, soffset * m_img_info->sector_size, imgtype)) == NULL)
    {
        fprintf(stderr, "filesystem img can not open\n");
        return 0;
    }
    
    EXT2FS_INFO *ext2fs = (EXT2FS_INFO *) fs_info;
    ext2fs_sb *sb = ext2fs->fs;
    EXT2_GRPNUM_T grp_num = 0;
 
    uint64_t journ_offset;

    journ_offset = (ext2fs->jinfo->start_blk * fs_info->block_size);
    int journ_numblk = tsk_getu32(TSK_BIG_ENDIAN, ext2fs->jinfo->fs->num_blk);

    int block_size = fs_info->block_size;

    tsk_fs_close(fs_info);
    tsk_img_close(m_img_info);

    FILE *hFile = NULL;

    if ((hFile = fopen(argv[1], "r+")) == 0)
        fprintf(stderr, "file open error!!\n");
    
    fseek(hFile, journ_offset + block_size, SEEK_SET);
    int tmp[1] = {0x00};
    int i;
    int temp = (journ_numblk) * block_size;

    for (i = 0; i < temp; i++) {
        fwrite(tmp, 1, 1, hFile);

    }
    fclose(hFile);

    printf("11\n");
    return 0;
}