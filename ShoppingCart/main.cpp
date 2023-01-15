#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Article
{
private :
    string model;
    double netprice, taxRate;
public :
    Article(string Model, double NetPrice, double TaxRate = 0.19)
    {
        model = Model;
        netprice = NetPrice;
        taxRate = netprice * TaxRate ;
    }
    virtual ~Article()
    {
        cout << "~Article() " << model;
    }
    void set_model(string name_Model)
    {
        model = name_Model;
    }
    void set_netPrice(double att_netprice)
    {
        netprice = att_netprice;
    }
    string get_model()
    {
        return model;
    }
    double get_netPrice()
    {
        return netprice;
    }
    double get_grossPrice()
    {
        double grossPrice;
        grossPrice = netprice + taxRate;
        return grossPrice;
    }
    virtual void print()=0;
};

class Accessory : public Article
{
private :
    bool original;
public :
    Accessory(string name_article, double Net_Price, bool Or = true) : Article(name_article, Net_Price)
    {
        original = Or;
    }
    virtual ~Accessory()
    {
        cout << "\n~Accessory() " ;

    }
    virtual void print(void)
    {
        cout << get_model() ;
        if (original == true)
            cout << " (original accessory)" << endl;
        else
            cout << endl;
    }
};

enum OperatingSystem {unknown, android, iOS, macOS, linux, proprietary, unix, windows};

ostream &operator<<(ostream &out, OperatingSystem x)
{
    if( x == unknown)
        return out << "unknown OS";
    else if( x == android)
        return out << "Android OS";
    else if( x == iOS)
        return out << "iOS";
    else if( x == macOS)
        return out << "MacOS";
    else if( x == linux)
        return out << "Linux  OS";
    else if( x == proprietary)
        return out << "proprietary  OS";
    else if( x == unix)
        return out << "Unix  OS";
    else if( x == windows)
        return out << "MS Windows OS";
}

class Device : public Article
{
private:
    int main_memory;
    OperatingSystem os;
public:
    Device(string Name_article, double Net_price, int memory_size, OperatingSystem Os = unknown)
    :Article(Name_article, Net_price)
    {
        main_memory = memory_size;
        os = Os;
    }
    virtual ~Device()
    {

        cout << "~Device() " << main_memory << endl;
    }
    OperatingSystem get_os()
    {
        return os;
    }
    virtual void print(void)
    {
        cout << get_model() << ", RAM " << main_memory << " GB , " << os;
    }
};

class Notebook : public Device
{
private :
    string drive;
    bool convertible;
public :
    Notebook(string NameArticle, double NetPrice, int Memory_Size, string Drive, OperatingSystem OS=linux, bool Conv=false)
    : Device(NameArticle, NetPrice, Memory_Size, OS)
    {
        drive = Drive;
        convertible = Conv;
    }
    virtual ~Notebook()
    {
        cout << "~Notebook()";
//        cout << "~Notebook()" << drive;
    }
    bool is_a_convertible()
    {
        return convertible;
    }
    virtual void print(void)
    {
        Device :: print();
        if(convertible == true)
            cout << " (convertible) " << drive;
    }
};

class Phone : public Device
{
public :
    Phone(string ArticleName, double NetPrice0, int Size_ofMemory, OperatingSystem OpS)
    :Device(ArticleName, NetPrice0, Size_ofMemory, OpS) {}

    virtual ~Phone()
    {
        cout << "~Phone()";
    }
    virtual void print(void)
    {
        Device :: print();
        cout << " phone";
    }
};

class InCart
{
private :
    Article *article;
    double amount;
    InCart *next;
public :
    InCart(Article *ar, double Amount=0, InCart *Next=nullptr)
    {
        article = ar;
        amount = Amount;
        next = Next;
    }
    virtual ~InCart()
    {
        cout << " ~Incart() " << amount;
        article->~Article();
    }
    InCart *get_next()
    {

        return next;
    }
    virtual void print()
    {

        cout << amount << " ";
        article->print();
        cout << endl << endl;
        cout << setw(50) << fixed << setprecision(2) << article->get_grossPrice() << " EUR" << "\t\t"
        << fixed << setprecision(2) << article->get_grossPrice()*amount
        << " EUR " << endl;
        cout << endl << setw(70) << "-------------" << endl << endl;
    }
};

class ShoppingCart
{
private :
    InCart *articles;
    double minFressShipping, sumNetPrice, sumGrossPrice;
public :
    ShoppingCart(InCart *Articles = nullptr, double MinFS = 1000, double SumNP = 0, double SumGP = 0)
    {
        articles = Articles;
        minFressShipping = MinFS;
        sumNetPrice = SumNP;
        sumGrossPrice = SumGP;
    }
    ~ShoppingCart()
    {
        cout << "~ShoppingCart()" << endl;
        while(articles != NULL)
        {
            cout << "delete article: ";
            delete articles;

        }
    }
    void set_minFreeShipping(double minFrSh)
    {
        minFressShipping = minFrSh;
    }
    void add_article(double Am, Article* a)
    {

        InCart *newInCart = new InCart(a,Am,articles);
        articles = newInCart;

        sumNetPrice += a->get_netPrice() * Am;
        sumGrossPrice += a->get_grossPrice() * Am;

    }
    virtual void print()
    {
        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl<<endl;
        cout << "+                        P R O T O - T E C - S H O P                         +" << endl<<endl;
        cout << "+                     Y O U R   S H O P P I N G C A R T                      +" << endl<<endl;
        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl<<endl;

        while(articles != nullptr)
        {
            articles->print();
            articles = articles->get_next();
        }
        delete articles;

        cout << setw(60) << "sum net price: " << fixed << setprecision(2) << sumNetPrice
        << " EUR" << endl << endl;
        cout << setw(60) << "tax: " << fixed << setprecision(2) << sumGrossPrice - sumNetPrice
        << " EUR" << endl << endl;
        cout << setw(60) << "sum gross price: " << fixed << setprecision(2) << sumGrossPrice
        << " EUR" << endl << endl;

        cout << setw(70) << "-------------" << endl<<endl;
        if(sumNetPrice >= minFressShipping)
            set_minFreeShipping(0);
        else
            set_minFreeShipping(5.90);
        cout << setw(60) << "shipping: " << fixed << setprecision(2) << minFressShipping
        << " EUR" << endl << endl;
        cout << setw(70) << "-------------" << endl << endl;
        cout << setw(60) << "total: " << fixed << setprecision(2) << sumGrossPrice + minFressShipping
        << " EUR" << endl << endl;
        cout << setw(70) << "=============" << endl << endl;

    }
};

int main()
{
    ShoppingCart ob;
    ob.set_minFreeShipping(500);

    Accessory *ac = new Accessory("YOOLOX 10k Wireless Powerbank Qi", 31.08, false);
    ob.add_article(3,ac);
    ob.print();

    Phone *p1 = new Phone("Samsung Galaxy S10+ SM-G975F/DS Dual SIM", 661.67, 8, android);
    ob.add_article(1,p1);

    Phone *p2 = new Phone("Apple iPhone 11 Pro 256GB", 1097.47, 4, iOS);
    ob.add_article(2,p2);

    Notebook *nt = new Notebook("ASUS ROG Strix Scar III G731", 1586.55, 16, "512GB SSD + 1TB SSHD" , windows);
    ob.add_article(1,nt);

    ob.print();

    delete ac;
    delete p1;
    delete p2;
    delete nt;

    return 0;
}
