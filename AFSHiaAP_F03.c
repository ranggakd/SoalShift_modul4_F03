#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

//macro
#define caesar 94
#define kunci 17
#define maxFilm 999
#define minFilm 0

//global variabel
static const char *dirpath = "/home/rak/shift4";
char cip[189];
char film[1000][1000];
pthread_t tid[1000];

//fumgsi caesar enkripsi
void enk(char str[],int counter)
{
	char kar;
	for(int i = 0; i < counter; i++)
	{
		kar = str[i];
		// printf("%c\n",kar);
		for(int j = 0; j < caesar+kunci ; j++)
		{
			// printf("%c_",cip[j]);
			if (kar == cip[j])
			{
				kar = cip[j+kunci];
				str[i]=kar;
				// printf("contoh%c\n",contoh[i]);
				break;
			}
		}
	}
}

//fungsi caesar dekripsi
void dek(char str[],int counter)
{
	char kar;
	for(int i = counter-1; i >= 0; i--)
	{
		kar = str[i];
		// printf("%c\n",kar);
		for(int j = caesar+kunci-1; j >=0 ; j--)
		{
			// printf("%c_",cip[j]);
			if (kar == cip[j])
			{
				kar = cip[j-kunci];
				str[i]=kar;
				// printf("contoh%c\n",contoh[i]);
				break;
			}
		}
	}
}

//fungsi searching film
int searchFilm(char *nama, int count)
{
	char fi[1000];
	sprintf(fi,"%s",nama);
	for (int i = 0; i <= count; i++)
	{
	printf("sf %d %s\n",i,fi);

		if (strcmp(film[i],fi)==0)
		{
			return 0;
		}
	}
	return 1;
}

//fungsi untuk thread
void* filterFilm(void* ptr)
{
	return NULL;
}

static void* xmp_init(struct fuse_conn_info *conn)
{
	//NO 2
	printf("init\n");
	char path[1000];
	char ipath[1000];
	char fpath[1000];
	char dpath[1000];
	sprintf(path,"/Videos");
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	sprintf(fpath,"%s%s",dirpath,dpath);
	sprintf(ipath,"%s/",dirpath);
	//buat dir
	mkdir(fpath,0777);
	//filter part film mkv
	// DIR *dp;
	// struct dirent *de;
	// dp=opendir(ipath);
	// if (dp == NULL)
	// {
	// 	printf("init filter gagal\n");
	// 	return (void*)conn;
	// }
	// while ((de=readdir(dp))!=NULL)
	// {
	// 	char filename[1000];
	// 	strcpy(filename,de->d_name);
	// 	//NO 1 dekrip
	// 	int counter=strlen(filename);
	// 	char kar;
	// 	for(int i = counter-1; i >= 0; i--)
	// 	{
	// 		//eksepsi
	// 		if (strcmp(filename,".")==0 || strcmp(filename,"..")==0)
	// 			break;
	// 		kar = filename[i];
	// 		// printf("%c\n",kar);
	// 		for(int j = caesar+kunci-1; j >=0 ; j--)
	// 		{
	// 			// printf("%c_",cip[j]);
	// 			if (kar == cip[j])
	// 			{
	// 				kar = cip[j-kunci];
	// 				filename[i]=kar;
	// 				// printf("contoh%c\n",contoh[i]);
	// 				break;
	// 			}
	// 		}
	// 	}
	// 	printf("init --> %s\n",filename);
	// 	//filter ekstensi film yang valid
	// 	char* nomor=malloc(sizeof(char*));
	// 	if ((nomor=strrchr(filename,'.'))!=NULL)
	// 	{
	// 		//nomor yang valid
	// 		// printf("->%s\n",nomor);
	// 		char no[5];
	// 		sprintf(no,"%s",nomor);
	// 		for (int i = 0; i < strlen(nomor)-1; i++)
	// 		{
	// 			if (i==strlen(nomor)-2)
	// 			{
	// 				no[3]='\0';
	// 				break;
	// 			}
	// 			no[i]=no[i+1];
	// 			no[i+1]=no[i+2];
	// 		}
	// 		int num;
	// 		num=atoi(no);
	// 		// printf("no %d\n",num);
	// 		if (num >= minFilm && num <= maxFilm)
	// 		{
	// 			nomor[0]='\0';
	// 			//ekstensi yang valid
	// 			char* ekstensi=malloc(sizeof(char*));
	// 			if ((ekstensi=strrchr(filename,'.'))!=NULL && strcmp(ekstensi,".mkv")==0)
	// 			{
	// 				for (int j = 0; j < strlen(filename)-1; j++)
	// 				{
	// 					if (j==strlen(filename)-1)
	// 					{
	// 						no[(int)strlen(filename)-1]='\0';
	// 						break;
	// 					}
	// 					filename[j]=filename[j+1];
	// 					filename[j+1]=filename[j+2];
	// 				}
	// 				printf("f %s\n",filename);
	// 				for (int i = 0; i <= maxFilm; i++)
	// 				{
	// 					if (strlen(film[i])==0 && searchFilm(filename,i))
	// 					{
	// 						//problem
	// 						strcpy(film[i],filename);
	// 						printf("film%d %s \n",i,film[i]);
	// 						break;
	// 					}
	// 				}
	// 			}
	// 		}
	// 		// if ((/* condition */))
	// 		// {
	// 		// 	/* code */
	// 		// }
			
	// 	}
		
		
	// }
	
	printf("end-init path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	return (void*)conn;
}

static void xmp_destroy(void *private_data)
{
	//NO 2
	printf("destroy\n");
	char path[1000];
	char fpath[1000];
	char dpath[1000];
	sprintf(path,"/Videos");
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("end-init path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	rmdir(fpath);
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
  	int res;
	char fpath[1000];
	char dpath[1000];
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("attr path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	res = lstat(fpath, stbuf);
	printf("mode %s %d\n",fpath,stbuf->st_mode);
	if (res == -1)
		return -errno;
	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  	char fpath[1000];
	printf("readdir path %s, dirpath %s\n",path,dirpath);
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{
		char dpath[1000];
		sprintf(dpath,"%s",path);
		//NO 1 enkrip
		int counter=strlen(dpath);
		//eksepsi
		if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
			enk(dpath,counter);
		printf("end-readdir path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
		sprintf(fpath,"%s%s",dirpath,dpath);		
	}
	//sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		//NO 4
		char cop[1000];
		sprintf(cop,"%s",de->d_name);
		//NO 1 dekrip
		int counter=strlen(de->d_name);
		//eksepsi
		if (strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0)
			dek(de->d_name,counter);
		//NO 3
		struct stat buff;
		char cek[1000];
		sprintf(cek,"%s/%s",dirpath,cop);
		printf("s%s\n",cek);
		lstat(cek,&buff);
		struct passwd *ps = malloc(sizeof(struct passwd*));
		struct group *gr = malloc(sizeof(struct group*));
		struct tm *tim = malloc(sizeof(struct tm*));
		ps = getpwuid(buff.st_uid);
		gr = getgrgid(buff.st_gid);
		time_t *atm = malloc(sizeof(time_t*));
		*atm = buff.st_atime;
		tim = localtime(atm);
		char waktu[1000];
		strftime(waktu,80,"%x-%T",tim);
		printf("waktu %s %s %s\n",waktu, ps->pw_name, gr->gr_name);
		if (((strcmp(ps->pw_name,"chipset"))==0 || (strcmp(ps->pw_name,"ic_controller"))==0)
		&& (strcmp(gr->gr_name,"rusak"))==0 && !(buff.st_mode & S_IRUSR & S_IRGRP & S_IROTH))
		{
			printf("masuk\n");
			char fm[1000];
			char loc[1000];
			sprintf(loc,"filemiris.txt");
			enk(loc,strlen(loc));
			sprintf(fm,"%s/%s",dirpath,loc);
			FILE *fil=fopen(fm,"a");
			fprintf(fil,"%s\t%d\t%d\t%s\n",de->d_name,ps->pw_uid,gr->gr_gid,waktu);
			fclose(fil);
			unlink(cek);
		}
		//NO 4
		char dr[1000];
		sprintf(dr,"%s/%s",fpath,cop);
		printf("de %s t%d\n",dr,de->d_type);
		// DIR *dd;
		if (strstr(dr,"/@ZA>AXio/")!=NULL && de->d_type!=4
		&& strstr(dr,"`[S%")==NULL)
		{
			printf("sss %s",dr);
			char to[1000];
			sprintf(to,"%s",dr);
			strcat(to,"`[S%");
			rename(dr,to);
			strcat(de->d_name,"`[S%");
			res = (filler(buf, de->d_name, &st, 0));
			if(res!=0) break;
		}
		res = (filler(buf, de->d_name, &st, 0));
		printf("red keluar\n");
		if(res!=0) break;
	}
	closedir(dp);
	return 0;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
	int res = 0;
	char fpath[1000];
	char dpath[1000];
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("end-mkdir path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	//NO 4
	if (strstr(fpath,"/@ZA>AXio/")!=NULL)
	{
		res = mkdir(fpath,0750);
		if (res == -1)
			return -errno;
		return 0;
	}
	else
	{
		res = mkdir(fpath,mode);
		if (res == -1)
			return -errno;
		return 0;	
	}
}

static int xmp_unlink(const char *path)
{
	int res;
	char fpath[1000];
	char dpath[1000];
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("end-unlink path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	//NO 2
	res = unlink(fpath);
	if (res == -1)
		return -errno;
	return 0;
}

static int xmp_rmdir(const char *path)
{
	int res = 0;
	char fpath[1000];
	char dpath[1000];
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("end-rmdir path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	//NO 2
	res = rmdir(fpath);
	if (res == -1)
		return -errno;
	return 0;
}

static int xmp_rename(const char *from, const char *to)
{
	int res = 0;
	char fpath[1000];
	char dpath[1000];
	char fpath2[1000];
	char dpath2[1000];
	sprintf(dpath,"%s",from);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(from,".")!=0 && strcmp(from,"..")!=0)
		enk(dpath,counter);
	printf("end-rename path %s, dekrip %s, dirpath %s\n",from,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	//enkrip to
	sprintf(dpath2,"%s",to);
	//NO 1 enkrip
	counter=strlen(dpath2);
	//eksepsi
	if (strcmp(to,".")!=0 && strcmp(to,"..")!=0)
		enk(dpath2,counter);
	printf("end-rename path %s, dekrip %s, dirpath %s\n",to,dpath2,dirpath);
	sprintf(fpath2,"%s%s",dirpath,dpath2);
	res = rename(fpath,fpath2);
	if (res == -1)
		return -errno;
	return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid)
{
	int res = 0;
	char fpath[1000];
	char dpath[1000];
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("end-chmod path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	res = lchown(fpath,uid,gid);
	if (res == -1)
		return -errno;
	return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
	int res = 0;
	char fpath[1000];
	char dpath[1000];
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("end-chmod path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	//NO 4
	if (strstr(fpath,"/@ZA>AXio/")!=NULL && strstr(fpath,"`[S%")!=NULL)
	{
		pid_t pid;
		int status;
		pid=fork();
		if (pid==0)
		{
			printf("File ekstensi iz1 tidak boleh diubah permissionnya.\n");			
			char *argv[5]={"zen","--error","--text='File ekstensi iz1 tidak boleh diubah permissionnya.\n'","--title='Pesan Error'",NULL};
			execv("/usr/bin/zenity",argv);
		}
		while ((wait(&status))>0);
		printf("iz1\n");			
		return 0;
	}
	else
	{
		res = chmod(fpath,mode);
		if (res == -1)
			return -errno;
		return 0;
	}
}

static int xmp_utimens(const char *path, const struct timespec ts[2])
{
	int res = 0;
	// (void)fi;
	struct timeval tv[2];
	tv[0].tv_sec = ts[0].tv_sec;
	tv[0].tv_usec = ts[0].tv_nsec / 1000;
	tv[1].tv_sec = ts[1].tv_sec;
	tv[1].tv_usec = ts[1].tv_nsec / 1000;
	char fpath[1000];
	char dpath[1000];
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("end-utimens path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	res = utimes(fpath, tv);
	if (res == -1)
		return -errno;
	return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
	int res = 0;
	char fpath[1000];
	char dpath[1000];
	sprintf(dpath,"%s",path);
	//NO 1 enkripsi
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("end-open path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	//NO 2
	res = open(fpath, fi->flags);
	if (res == -1)
		return -errno;
	close(res);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  	char fpath[1000];
	printf("read path %s, dirpath %s\n",path,dirpath);
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{
		char dpath[1000];
		sprintf(dpath,"%s",path);
		//NO 1 enkrip
		int counter=strlen(dpath);
		//eksepsi
		if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
			enk(dpath,counter);
		printf("end-read path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
		sprintf(fpath,"%s%s",dirpath,dpath);
	}
	int res = 0;
	int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_write(const char *path, const char *buf, size_t size,
off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int res;
	(void)fi;
	char fpath[1000];
	printf("write path %s, dirpath %s\n",path,dirpath);
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{
		char dpath[1000];
		sprintf(dpath,"%s",path);
		//NO 1 enkrip
		int counter=strlen(dpath);
		//eksepsi
		if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
			enk(dpath,counter);
		printf("end-write path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
		sprintf(fpath,"%s%s",dirpath,dpath);
	}
	//NO 2
	fd = open(fpath, O_WRONLY);
	if (fd == -1)
		return -errno;
	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;
	close(fd);
	return res;
}

static int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
	int res = 0;
	// (void)fi;
	char fpath[1000];
	char dpath[1000];
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("end-create path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	//NO 4
	if (strstr(fpath,"/@ZA>AXio/")!=NULL)
	{
		res = creat(fpath,0640);
		// char from[1000];
		// sprintf(from,"%s",fpath);
		// strcat(fpath,"`[S%");	
		// res = rename(from,fpath);
		// res = open(fpath,fi->flags);
		// res = utimes(fpath,)
		if (res == -1)
			return -errno;
		close(res);
		printf("ss %s\n",fpath);
		return 0;
	}
	else
	{
		res = creat(fpath,mode);
		if (res == -1)
			return -errno;
		close(res);
		return 0;
	}
	
	return 0;
}

static int xmp_release(const char *path, struct fuse_file_info *fi)
{
	char fpath[1000];
	char dpath[1000];
	sprintf(dpath,"%s",path);
	//NO 1 enkrip
	int counter=strlen(dpath);
	//eksepsi
	if (strcmp(path,".")!=0 && strcmp(path,"..")!=0)
		enk(dpath,counter);
	printf("end-open path %s, dekrip %s, dirpath %s\n",path,dpath,dirpath);
	sprintf(fpath,"%s%s",dirpath,dpath);
	//NO 2
	(void)fpath;
	(void)fi;
	return 0;
}

static struct fuse_operations xmp_oper = {
	.init		= xmp_init,		//no1 no2
	.destroy	= xmp_destroy,	//no1 no2
	.getattr	= xmp_getattr,	//no1
	.readdir	= xmp_readdir,	//no1 no4 no3
	.mkdir		= xmp_mkdir,	//no1 no4
	.unlink		= xmp_unlink,	//no1 no2	
	.rmdir		= xmp_rmdir,	//no1 no2
	.rename		= xmp_rename,	//no1 no4
	.chmod		= xmp_chmod,	//no1 no4	
	.chown		= xmp_chown,	//no1 no3	
	.utimens	= xmp_utimens,	//no1
	.open		= xmp_open,		//no1 no2
	.read		= xmp_read,		//no1
	.write		= xmp_write,	//no1 no2
	.create		= xmp_create,	//no1 no4
	.release	= xmp_release,	//no1 no2
};

int main(int argc, char *argv[])
{
	strcpy(cip,"qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0");
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
