 clear
 clc
fid= fopen("data_without_row_no.csv", "w+");
i=1;
time=now();
for t=0:1e-3:500-0.001;
wt=t*2*pi*50;
const=400*sqrt(2/3);
a=const*sin(wt-2*pi/3);
b=const*sin(wt-2*pi/3);
c=const*sin(wt+2*pi/3);
 %fprintf(fid,"%d,",i);
t1= addtodate(time, t, 'second');
aaa=datestr(t1,'yyyy-mm-dd HH:MM:SS.FFF');
 fprintf(fid,"%s,",aaa);
 fprintf(fid,"%.15f,",a)
 fprintf(fid,"%.15f,",b)
 fprintf(fid,"%.15f,",c)
  fprintf(fid,"%d,",randi(2)-1)
   fprintf(fid,"%d,",randi(2)-1)
    fprintf(fid,"%d,",randi(2)-1)
     fprintf(fid,"%d,",randi(2)-1)
      fprintf(fid,"%d,",randi(2)-1)
       fprintf(fid,"%d,",randi(2)-1)
        fprintf(fid,"%d,",randi(2)-1)
         fprintf(fid,"%d\n",randi(2)-1)

i++;

%2011-11-29 20:18:29.233 'yyyy-mm-dd HH:MM:SS.FFF'
endfor

 fclose ("all");
 %aaa=datestr(t1,'mmmm dd, yyyy HH:MM:SS.FFF AM');
 %fprintf(fid,"%f\n",a)
%rows(file)
%A=randi([0 1],rows(file),8);
%file=[file,A];


 %plot(file(:,1),file(:,2))
 %hold on
 %plot(file(:,1),file(:,3))
 %plot(file(:,1),file(:,4))

 %t = datenum('06-Jul-2020 23:00:00');
%datestr(t)

%t= addtodate(t, 1, 'millisecond');
%datestr(now,'mmmm dd, yyyy HH:MM:SS.FFF AM')