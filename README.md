# SoalShift_modul4_F03
Keperluan tugas laboratorium Sistem Operasi 2019

<center>

![image](cover.gif "Userspace?")

</center>

---

# NO 1
Mendefinisikan makro
```c
#define caesar 94
#define kunci 17
```

Mendefinisikan global variabel untuk path dan urutan karakter cipher
```c
static const char *dirpath = "/home/rak/shift4";
char cip[189];
```

Membuat fungsi caesar enkripsi
```c
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
```

Membuat fungsi caesar dekripsi
```c
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
```

Fungsi enkripsi dipanggil di semua operasi fungsi fuse yang menerima parameter path. Fungsi dekripsi dipanggil di operasi fungsi fuse readdir saja.  

Pada main program, isikan seluruh karakter dari soal sebanyak 2x pada array global.

# NO 4

Pada fungsi mkdir tambahkan kondisi untuk mengantisipasi folder YOUTUBER.
```c
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
```

Pada fungsi create tambahkan kondisi untuk mengantisipasi file yang dibuat di dalam YOUTUBER.
```c
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
```

Mendefinisikan fungsi operasi fuse rename agar dapat membubuhi file dengan .iz1.
```c
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
```

Pada fungsi readdir, untuk mengantisipasi file yang berada di YOUTUBER agar berekstensi .iz1 dilakukan branching.
```c
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
```

## Selain Itu

Untuk selain soal diatas masih belum dominan benar dan belum diselesaikan seluruhnya. Mohon maaf dan terimakasih. Selamat menunaikan ibadah puasa, semuanya.
