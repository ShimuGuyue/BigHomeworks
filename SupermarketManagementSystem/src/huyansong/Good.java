package huyansong;

// 定义商品类
public class Good {
    String type;            // 类别
    String name;            // 名称
    int price;              // 价格
    int remain;             // 库存量
    String manufacturer;    // 生产厂家
    String brand;           // 品牌

    Good(String type, String name, int price, int remain, String manufacturer, String brand) {
        this.type = type;
        this.name = name;
        this.price = price;
        this.remain = remain;
        this.manufacturer = manufacturer;
        this.brand = brand;
    }
}
