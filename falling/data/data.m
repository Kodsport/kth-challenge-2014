D = [1 2 3 4 5 6 7 8 9 10 1e3+[0 1 2 3] 12345 2e5-[0 1 2 3 4 5 6]]

for i = 1:length(D)
    d = D(i);
    fid = fopen(sprintf('secret/%02d.in',i),'w');
    fprintf(fid,'%d\n',D(i));
    fclose(fid);
    
    fid = fopen(sprintf('secret/%02d.ans',i),'w');
	if mod(d,2) == 1
		fprintf(fid,'%d %d\n',(d-1)/2,(d+1)/2);
    elseif (mod(d,4) == 0)
		fprintf(fid,'%d %d\n',d/4-1,d/4+1);
    else
        fprintf(fid,'impossible\n');
    end
    fclose(fid);
end