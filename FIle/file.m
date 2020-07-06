 clear
 clc
 t=0:1e-3:500;
 wt=t*2*pi*50;
file(:,1)=wt';
const=400*sqrt(2/3);
file(:,3)=const*sin(file(:,1));
file(:,4)=const*sin(file(:,1)-2*pi/3);
file(:,5)=const*sin(file(:,1)+2*pi/3);
i=1;
time=now();
for t=0:1e-3:500;
file(i,1)=i;
t1= addtodate(time, t, 'second');
file(i,2)=t1;%datestr(t1,'mmmm dd, yyyy HH:MM:SS.FFF AM');
i++;
endfor

%rows(file)
A=randi([0 1],rows(file),8);
file=[file,A];


 plot(file(:,1),file(:,2))
 hold on
 plot(file(:,1),file(:,3))
 plot(file(:,1),file(:,4))

 %t = datenum('06-Jul-2020 23:00:00');
%datestr(t)

%t= addtodate(t, 1, 'millisecond');
%datestr(now,'mmmm dd, yyyy HH:MM:SS.FFF AM')