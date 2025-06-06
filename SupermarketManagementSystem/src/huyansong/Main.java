package huyansong;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        // 创建超市对象并调用菜单方法
        Supermarket supermarket = new Supermarket();
        supermarket.Menu();
    }
}
