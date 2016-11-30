/*
   Key Value System
   Copyright (C) 2016 Hung-Wei Tseng, Ph.D. <hungwei_tseng@ncsu.edu>

   This program can be distributed under the terms of the GNU GPLv3.
   See the file COPYING.

   This code is derived from function prototypes found /usr/include/fuse/fuse.h
   Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
   His code is licensed under the LGPLv2.
   A copy of that code is included in the file fuse.h

   The point of this FUSE filesystem is to provide an introduction to
   FUSE.  It was my first FUSE filesystem as I got to know the
   software; hopefully, the comments in this code will help people who
   follow later to get a gentler introduction.

*/

///////////////////////////////////////////////////////////////////
//                                                               //
//                                                               //
// Name                Unity Ids                                 //
// Laxman Sole         lsole                                     //
// Aditya Gulavani     agulava                                   //
// Mahita Nagabhiru    mnagabh                                   //
// Anmol  Nayak        anayak2                                   //
//                                                               //
//                                                               //
///////////////////////////////////////////////////////////////////
#include "kvfs.h"

char * check_path(const char * path){
	char *relative = (char *) malloc(1024*sizeof(char));
	sprintf(relative, KVFS_DATA->rootdir);
	strcat(relative, "/");
	strcat(relative, path);

	if(strcmp(path, "6666cd76f96956469e7be39d750cc7d9") == 0)
	{
		log_msg("\tROOT_DIR = %s\n",KVFS_DATA->rootdir);
		return KVFS_DATA->rootdir;
	}
	/* log_msg("relative = %s \npath = %s\n",relative, path); */
	log_msg("\trelative = %s\n",relative);
	return relative;
}

///////////////////////////////////////////////////////////
//
// Prototypes for all these functions, and the C-style comments,
// come from /usr/include/fuse.h
//

/** Get file attributes.
 *
 * Similar to stat().  The 'st_dev' and 'st_blksize' fields are
 * ignored.  The 'st_ino' field is ignored except if the 'use_ino'
 * mount option is given.
 */
int kvfs_getattr_impl(const char *path, struct stat *statbuf) {
	log_msg("\nkvfs_getattr_impl called  ");
	int status;

	// md5 for /mnt/lsole: 9dc7ba184fa184338cd1646f964d4baf
	char * updated = check_path(path);
	/* log_msg("In getattr: updated = %s\n",updated); */
	status = lstat(updated, statbuf);
	// free(updated);

	if(status == -1)
		return -errno;

	return 0;
}

/** Read the target of a symbolic link
 *
 * The buffer should be filled with a null terminated string.  The
 * buffer size argument includes the space for the terminating
 * null character.  If the linkname is too long to fit in the
 * buffer, it should be truncated.  The return value should be 0
 * for success.
 */
// Note the system readlink() will truncate and lose the terminating
// null.  So, the size passed to to the system readlink() must be one
// less than the size passed to kvfs_readlink()
// kvfs_readlink() code by Bernardo F Costa (thanks!)
int kvfs_readlink_impl(const char *path, char *link, size_t size) {
	log_msg("\nkvfs_readlink_impl called  ");
	return 0;
}

/** Create a file node
 *
 * There is no create() operation, mknod() will be called for
 * creation of all non-directory, non-symlink nodes.
 */
// shouldn't that comment be "if" there is no.... ?
int kvfs_mknod_impl(const char *path, mode_t mode, dev_t dev) {
	log_msg("\nkvfs_mknod_impl called, %d", mode);

	int status;
	char * updated = check_path(path);
	/* if (S_ISFIFO(mode))
		status = mkfifo(updated, mode);
	else */
	status = mknod(updated, mode, dev);
	// free(updated);
	if (status == -1)
		return -errno;

	return 0;
}

/** Create a directory */
int kvfs_mkdir_impl(const char *path, mode_t mode) {
	log_msg("\nkvfs_mkdir_impl called  ");

	char * updated = check_path(path);
	int status = mkdir(updated,mode);
	// free(updated);

	if(status == -1)
		return -errno;
	return 0;
}

/** Remove a file */
int kvfs_unlink_impl(const char *path) {
	log_msg("\nkvfs_unlink_impl called  ");

	char * updated = check_path(path);
	int status =unlink(updated);
	// free(updated);

	if(status == -1)
		return -errno;
	return 0;
}

/** Remove a directory */
int kvfs_rmdir_impl(const char *path) {
	log_msg("\nkvfs_rmdir_impl called  ");
	char * updated = check_path(path);
	int status = rmdir(updated);
	// free(updated);

	if(status == -1)
		return -errno;
	return 0;
}

/** Create a symbolic link */
// The parameters here are a little bit confusing, but do correspond
// to the symlink() system call.  The 'path' is where the link points,
// while the 'link' is the link itself.  So we need to leave the path
// unaltered, but insert the link into the mounted directory.
int kvfs_symlink_impl(const char *path, const char *link) {
	log_msg("\nkvfs_symlink_impl called  ");
	//char * updated  = check_path(path);
	char * updated2 = check_path(link);
	int status = symlink(path, updated2);
	// free(updated2);

	if(status == -1)
		return -errno;
	return 0;
}

/** Rename a file */
// both path and newpath are fs-relative
int kvfs_rename_impl(const char *path, const char *newpath) {
	log_msg("\nkvfs_rename_impl called  ");
	char * updated  = check_path(path);
	char * updated2 = check_path(newpath);
	int status = rename(updated,updated2);
	// free(updated);
	// free(updated2);

	if(status == -1)
		return -errno;
	return 0;
}

/** Create a hard link to a file */
int kvfs_link_impl(const char *path, const char *newpath) {
	log_msg("\nkvfs_link_impl called  ");
	char * updated  = check_path(path);
	char * updated2 = check_path(newpath);
	int status = link(updated,updated2);
	// free(updated);
	// free(updated2);

	if(status == -1)
		return -errno;
	return 0;
}

/** Change the permission bits of a file */
int kvfs_chmod_impl(const char *path, mode_t mode) {
	log_msg("\nkvfs_chmod_impl called  ");
	char * updated = check_path(path);
	int status = chmod(updated,mode);
	// free(updated);

	if(status == -1)
		return -errno;
	return 0;
}

/** Change the owner and group of a file */
int kvfs_chown_impl(const char *path, uid_t uid, gid_t gid) {
	log_msg("\nkvfs_chown_impl called  ");
	char * updated = check_path(path);
	int status = lchown(updated,uid,gid);
	// free(updated);

	if(status == -1)
		return -errno;
	return 0;
}

/** Change the size of a file */
int kvfs_truncate_impl(const char *path, off_t newsize) {
	log_msg("\nkvfs_truncate_impl called  newsize=%d",newsize);
	char * updated = check_path(path);
	int status = truncate(updated,newsize);
	// free(updated);

	if(status == -1)
		return -errno;
	return 0;
}

/** Change the access and/or modification times of a file */
/* note -- I'll want to change this as soon as 2.6 is in debian testing */
int kvfs_utime_impl(const char *path, struct utimbuf *ubuf) {
	log_msg("\nkvfs_utime_impl called  ");

	char * updated = check_path(path);
	int status = utime(updated, ubuf);
	// free(updated);

	if (status == -1)
		return -errno;

	return 0;
}

/** File open operation
 *
 * No creation, or truncation flags (O_CREAT, O_EXCL, O_TRUNC)
 * will be passed to open().  Open should check if the operation
 * is permitted for the given flags.  Optionally open may also
 * return an arbitrary filehandle in the fuse_file_info structure,
 * which will be passed to all file operations.
 *
 * Changed in version 2.2
 */
int kvfs_open_impl(const char *path, struct fuse_file_info *fi) {
	log_msg("\nkvfs_open_impl called %d", fi->flags);

	char * updated = check_path(path);
	int fd = open(updated, fi->flags);
	// free(updated);

	if (fd == -1)
		return -errno;

	fi->fh = fd;
	// log_msg("\n\nOpened a file with FD = %d\n\n", fd);
	return 0;
}

/** Read data from an open file
 *
 * Read should return exactly the number of bytes requested except
 * on EOF or error, otherwise the rest of the data will be
 * substituted with zeroes.  An exception to this is when the
 * 'direct_io' mount option is specified, in which case the return
 * value of the read system call will reflect the return value of
 * this operation.
 *
 * Changed in version 2.2
 */
// I don't fully understand the documentation above -- it doesn't
// match the documentation for the read() system call which says it
// can return with anything up to the amount of data requested. nor
// with the fusexmp code which returns the amount of data also
// returned by read.
int kvfs_read_impl(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
	log_msg("\nkvfs_read_impl called  ");

	char * updated = check_path(path);
	int fd = open(updated, O_RDONLY);
	// free(updated);

	if (fd == -1)
		return -errno;

	int status = pread(fd, buf, size, offset);
	if (status == -1)
		status = -errno;

	/* close(fd); */
	return status;
}

/** Write data to an open file
 *
 * Write should return exactly the number of bytes requested
 * except on error.  An exception to this is when the 'direct_io'
 * mount option is specified (see read operation).
 *
 * Changed in version 2.2
 */
// As  with read(), the documentation above is inconsistent with the
// documentation for the write() system call.
int kvfs_write_impl(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
	log_msg("\nkvfs_write_impl called size= %d , %d",size,offset);

	char * updated = check_path(path);
	/* int fd = open(updated, O_RDWR | O_APPEND | O_CREAT, S_IRWXU); */
	int fd = open(updated, O_WRONLY);
	// free(updated);

	if (fd == -1)
		return -errno;

	// log_msg("\n\nWriting a file with FD = %d\n\n", fi->fh);
	int status = pwrite(fd, buf, size, offset);

	log_msg("\nkvfs_write_impl called status= %d",status);
	if (status == -1)
		return -errno;
	return status;
}

/** Get file system statistics
 *
 * The 'f_frsize', 'f_favail', 'f_fsid' and 'f_flag' fields are ignored
 *
 * Replaced 'struct statfs' parameter with 'struct statvfs' in
 * version 2.5
 */
int kvfs_statfs_impl(const char *path, struct statvfs *statv) {
	log_msg("\nkvfs_statfs_impl called  ");

	char * updated = check_path(path);
	//int status = statvfs(path, statv);
	int status = statvfs(updated, statv);
	// free(updated);

	if(status == -1)
		return -errno;

	return 0;
}

/** Possibly flush cached data
 *
 * BIG NOTE: This is not equivalent to fsync().  It's not a
 * request to sync dirty data.
 *
 * Flush is called on each close() of a file descriptor.  So if a
 * filesystem wants to return write errors in close() and the file
 * has cached dirty data, this is a good place to write back data
 * and return any errors.  Since many applications ignore close()
 * errors this is not always useful.
 *
 * NOTE: The flush() method may be called more than once for each
 * open().  This happens if more than one file descriptor refers
 * to an opened file due to dup(), dup2() or fork() calls.  It is
 * not possible to determine if a flush is final, so each flush
 * should be treated equally.  Multiple write-flush sequences are
 * relatively rare, so this shouldn't be a problem.
 *
 * Filesystems shouldn't assume that flush will always be called
 * after some writes, or that if will be called at all.
 *
 * Changed in version 2.2
 */
// this is a no-op in BBFS.  It just logs the call and returns success
int kvfs_flush_impl(const char *path, struct fuse_file_info *fi) {
	/* log_msg("\n\nkvfs_flush(path=\"%s\", fi=0x%08x)  ", path, fi); */
	// no need to get fpath on this one, since I work from fi->fh not the path
	/* log_fi(fi); */
	log_msg("\nkvfs_flush_impl called  ");

	char * updated = check_path(path);
	int fd = open(updated, O_WRONLY);
	// free(updated);

	if (fd == -1)
		return -errno;

	int status = close(dup(fd));
	if(status == -1)
		return -errno;

	return 0;
}

/** Release an open file
 *
 * Release is called when there are no more references to an open
 * file: all file descriptors are closed and all memory mappings
 * are unmapped.
 *
 * For every open() call there will be exactly one release() call
 * with the same flags and file descriptor.  It is possible to
 * have a file opened more than once, in which case only the last
 * release will mean, that no more reads/writes will happen on the
 * file.  The return value of release is ignored.
 *
 * Changed in version 2.2
 */
int kvfs_release_impl(const char *path, struct fuse_file_info *fi) {
	log_msg("\nkvfs_release_impl called\n\n\n\n");

	int status = close(fi->fh);
	if(status == -1)
		return -errno;

	return 0;
}

/** Synchronize file contents
 *
 * If the datasync parameter is non-zero, then only the user data
 * should be flushed, not the meta data.
 *
 * Changed in version 2.2
 */
int kvfs_fsync_impl(const char *path, int datasync, struct fuse_file_info *fi) {
	log_msg("\nkvfs_fsync_impl called  ");

	int status;
	if(datasync)
		status = fdatasync(fi->fh);
	else
		status = fsync(fi->fh);

	if(status == -1)
		return -errno;

	return 0;
}

#ifdef HAVE_SYS_XATTR_H
/** Set extended attributes */
int kvfs_setxattr_impl(const char *path, const char *name, const char *value, size_t size, int flags) {
	log_msg("\nkvfs_setxattr_impl called  ");
	return 0;
	return -1;
}

/** Get extended attributes */
int kvfs_getxattr_impl(const char *path, const char *name, char *value, size_t size) {
	log_msg("\nkvfs_getxattr_impl called  ");
	return 0;
	return -1;
}

/** List extended attributes */
int kvfs_listxattr_impl(const char *path, char *list, size_t size) {
	log_msg("\nkvfs_listxattr_impl called  ");
	int status = llistxattr(path, list, size);
	if (status == -1)
		return -errno;
	return status;
}

/** Remove extended attributes */
int kvfs_removexattr_impl(const char *path, const char *name)
{
	log_msg("\nkvfs_removexattr_impl called  ");
	return 0;
	return -1;
}
#endif

/** Open directory
 *
 * This method should check if the open operation is permitted for
 * this  directory
 *
 * Introduced in version 2.3
 */
int kvfs_opendir_impl(const char *path, struct fuse_file_info *fi) {
	DIR *dh=NULL;
	log_msg("\nkvfs_opendir_impl called  ");

	char * updated = check_path(path);

	dh = opendir(updated);
	// free(updated);

	if(dh == NULL)
		return -errno;

	fi->fh = (unsigned long) dh;
	return 0;
}

/** Read directory
 *
 * This supersedes the old getdir() interface.  New applications
 * should use this.
 *
 * The filesystem may choose between two modes of operation:
 *
 * 1) The readdir implementation ignores the offset parameter, and
 * passes zero to the filler function's offset.  The filler
 * function will not return '1' (unless an error happens), so the
 * whole directory is read in a single readdir operation.  This
 * works just like the old getdir() method.
 *
 * 2) The readdir implementation keeps track of the offsets of the
 * directory entries.  It uses the offset parameter and always
 * passes non-zero offset to the filler function.  When the buffer
 * is full (or an error happens) the filler function will return
 * '1'.
 *
 * Introduced in version 2.3
 */

int kvfs_readdir_impl(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
	log_msg("\nkvfs_readdir_impl called  ");

	DIR *dp;
	struct dirent *de;

	char * updated = check_path(path);
	dp = opendir(updated);
	// free(updated);

	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		if (filler(buf, de->d_name, &st, 0))
			break;
	}

	closedir(dp);
	return 0;
}

/** Release directory
 *
 * Introduced in version 2.3
 */
int kvfs_releasedir_impl(const char *path, struct fuse_file_info *fi) {
	log_msg("\nkvfs_releasedir_impl called\n\n\n\n");
	int status = closedir((DIR *) (unsigned long) fi->fh);

	if(status == -1)
		return -errno;

	return 0;
}

/** Synchronize directory contents
 *
 * If the datasync parameter is non-zero, then only the user data
 * should be flushed, not the meta data
 *
 * Introduced in version 2.3
 */
// when exactly is this called?  when a user calls fsync and it
// happens to be a directory? ??? >>> I need to implement this...
int kvfs_fsyncdir_impl(const char *path, int datasync, struct fuse_file_info *fi) {
	log_msg("\nkvfs_fsyncdir_impl called  ");
	return 0;
}

int kvfs_access_impl(const char *path, int mask) {
	int status = 0;
	log_msg("\nkvfs_access_impl called, mask = %d", mask);
	/* log_msg("\n%s  ",path); */

	char * updated = check_path(path);

	status = access(updated, mask);
	// free(updated);

	if(status == -1)
		return -errno;

	return 0;
}

/**
 * Create and open a file
 *
 * If the file does not exist, first create it with the specified
 * mode, and then open it.
 *
 * If this method is not implemented or under Linux kernel
 * versions earlier than 2.6.15, the mknod() and open() methods
 * will be called instead.
 *
 * Introduced in version 2.5
 */
// Not implemented.  I had a version that used creat() to create and
// open the file, which it turned out opened the file write-only.
/**
 * Change the size of an open file
 *
 * This method is called instead of the truncate() method if the
 * truncation was invoked from an ftruncate() system call.
 *
 * If this method is not implemented or under Linux kernel
 * versions earlier than 2.6.15, the truncate() method will be
 * called instead.
 *
 * Introduced in version 2.5
 */
int kvfs_ftruncate_impl(const char *path, off_t offset, struct fuse_file_info *fi) {
	log_msg("\nkvfs_ftruncate_impl called offset= %d",offset);

	int status = ftruncate(fi->fh, offset);
	if (status == -1)
		return -errno;
	return 0;
}

/**
 * Get attributes from an open file
 *
 * This method is called instead of the getattr() method if the
 * file information is available.
 *
 * Currently this is only called after the create() method if that
 * is implemented (see above).  Later it may be called for
 * invocations of fstat() too.
 *
 * Introduced in version 2.5
 */
int kvfs_fgetattr_impl(const char *path, struct stat *statbuf, struct fuse_file_info *fi) {
	log_msg("\nkvfs_fgetattr_impl called  ");

	char * updated = check_path(path);
	int fd = open(updated, O_RDONLY);
	// free(updated);
	
	if (fd == -1)
		return -errno;

	int status = fstat(fd, statbuf);
	if (status == -1)
		return -errno;

	return 0;
}

