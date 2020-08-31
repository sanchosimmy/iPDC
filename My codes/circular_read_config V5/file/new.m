 clear
 clc
fid= fopen("data_without_row_no_final.csv", "w+");
i=1;
const1=0;
time=now();
for t=0:1e-3:50-0.001;
wt=t*2*pi*50;
if(t==10)
const1=1;
endif
const=400*sqrt(2/3);
a=const*sin(wt)+25*const*const1*exp(-1*t/5);
b=const*sin(wt-2*pi/3);
c=const*sin(wt+2*pi/3);
%d=const*sin(wt-2*pi/3)*randi(2);
%e=const*sin(wt-2*pi/3)*randi(2);
%f=const*sin(wt+2*pi/3)*randi(2);
% fprintf(fid,"%d,",i);
t1= addtodate(time, t, 'second');
aaa=datestr(now(),'dd/mm/yyyy,HH:MM:SS.FFF');
 fprintf(fid,"%s,",aaa);
 fprintf(fid,"%.15f,",a)
 fprintf(fid,"%.15f,",b)
 fprintf(fid,"%.15f,",c)
 % fprintf(fid,"%.15f,",d)
 %fprintf(fid,"%.15f,",e)
 %fprintf(fid,"%.15f,",f)
  fprintf(fid,"%d,",randi(2)-1)
   fprintf(fid,"%d,",randi(2)-1)
    fprintf(fid,"%d,",randi(2)-1)
     fprintf(fid,"%d,",randi(2)-1)
      fprintf(fid,"%d,",randi(2)-1)
       fprintf(fid,"%d,",randi(2)-1)
             fprintf(fid,"%d,",randi(2)-1)
         fprintf(fid,"%d,",randi(2)-1)
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