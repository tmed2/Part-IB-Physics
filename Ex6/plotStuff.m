hold on;
dimentionM = size(M);
for i =2:dimentionM(2)
    plot(M(:,1),M(:,i));
    %plot(M(:,1),M(:,i) + 0.01, '-r')
    %plot(M(:,1),M(:,i) - 0.01 , '-r')
end
hold off;