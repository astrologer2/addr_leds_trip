class RGBColor {
  private:
    int r, g, b;
  public:
    RGBColor(int rr, int gg, int bb) {
      r = rr;
      g = gg;
      b = bb;
    }
    RGBColor() {
      r = 0;
      g = 0;
      b = 0;
    }
    int getR(){
      return r;
    }
    int getG(){
      return g;
    }
    int getB(){
      return b;
    }
    RGBColor& operator = (RGBColor x){
      r=x.r;
      g=x.g;
      b=x.b;
      return *this;
    }
    void hue2rgb(int hueC) {
      hueC %= 360;
      int bC = hueC / 60;
      int aC = hueC % 60;
      switch (bC) {
        case 0:
          r = 255;
          g = int(map(aC, 0, 59, 0, 255));
          b = 0;
          break;
        case 1:
          r = int(map(aC, 0, 59, 255, 0));
          g = 255;
          b = 0;
          break;
        case 2:
          r = 0;
          g = 255;
          b = int(map(aC, 0, 59, 0, 255));
          break;
        case 3:
          r = 0;
          g = int(map(aC, 0, 59, 255, 0));
          b = 255;
          break;
        case 4:
          r = int(map(aC, 0, 59, 0, 255));
          g = 0;
          b = 255;
          break;
        case 5:
          r = 255;
          g = 0;
          b = int(map(aC, 0, 59, 255, 0));
          break;
        default:
          break;
      };
    }
    void bri2rgb(int briC) {
      if (briC > 100)briC = 100;
      r = r * briC / 100;
      g = g * briC / 100;
      b = b * briC / 100;
    }

    void sat2rgb(int satC) {
      if (satC > 100)satC = 100;
      int avg = max(b, max(r, g));
      r = (r * satC / 100) + (avg * (100 - satC)) / 100;
      g = (g * satC / 100) + (avg * (100 - satC)) / 100;
      b = (b * satC / 100) + (avg * (100 - satC)) / 100;
    }
    void hsb2rgb(int hueC, int satC, int briC) {
      hue2rgb(hueC);
      sat2rgb(satC);
      bri2rgb(briC);
    }

};
