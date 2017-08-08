hold on;
dimentionE = size(E);
for i = 2:dimentionE(2)
    plot(E(:,1),E(:,i));
end
hold off;