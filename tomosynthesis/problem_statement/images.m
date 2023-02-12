x0 = [0 2 2]-1;
y0 = [0 0 2]-1;
r = [1 .5 2]/2;
angles = [23 -45];
for a = angles
    alpha = a*pi/180;
    x1 = y0*cos(alpha)-x0*sin(alpha);
    
    x = -2.5:.02:2.5;
    t = 0*x;
    for i = 1:length(r)
        t = t + real(2*sqrt(r(i)^2-(x1(i)-x).^2));
    end
    I = exp(-.6*t)*1.3-.4;
    I = exp(-t)-.1;
    figure(a+100);
    imagesc(x,0,I)
    colormap('gray')
    caxis([0 1])
    imwrite(I,sprintf('image%d.png',a))
end