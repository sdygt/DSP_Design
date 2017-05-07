fp = fopen('source.dat','w');
y = audioread('source.wav','native');
fprintf(fp,'1651 2 0 0 %d\n',length(y));
for word = y
    fprintf(fp,'%d\n',word);
end
    