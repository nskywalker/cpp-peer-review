#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <cassert>

using namespace std;

class Domain {
    std::string domain;
    // разработайте класс домена
    static std::string ReverseDomain(const std::string& str) {
        std::string res = str;
        std::reverse(res.begin(), res.end());
        return res;
    }
public:
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами
    Domain(const std::string& domain_) : domain(ReverseDomain(domain_) + '.'){}

    // разработайте operator==
    bool operator==(const Domain& other) const {
        return this->domain == other.domain;
    }

    bool operator<(const Domain& other) const {
        return std::lexicographical_compare(domain.begin(), domain.end(), other.domain.begin(), other.domain.end());
    }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& other) const {
        if (other.domain.size() > domain.size()) {
            return false;
        }
        std::string_view domain_ = other.domain;
        std::string_view sub_domain = domain;
        sub_domain.remove_suffix(sub_domain.size() - domain_.size());
        return domain_ == sub_domain;
//        return ReverseDomain(other.domain).find(ReverseDomain(domain)) != std::string::npos;
    }
};

class DomainChecker {
    std::vector<Domain> forb_dom;
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template<class InputIt> DomainChecker(InputIt begin, InputIt end) : forb_dom({begin, end}){
        std::sort(forb_dom.begin(), forb_dom.end());
        auto last = std::unique(forb_dom.begin(), forb_dom.end(), [](const Domain& lhs, const Domain& rhs){
            return lhs.IsSubdomain(rhs) or rhs.IsSubdomain(lhs);
        });
        forb_dom.erase(last, forb_dom.end());
    }

    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain& other) {
//        return std::any_of(forb_dom.begin(), forb_dom.end(), [&](const Domain& domain){return other.IsSubdomain(domain);});
        auto it = std::upper_bound(forb_dom.begin(), forb_dom.end(), other,[](const Domain& domain, const Domain& val)
        {return domain < val;});
        return it != forb_dom.begin() and other.IsSubdomain(*(--it));
    }
};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

template <typename Number>
std::vector<Domain> ReadDomains(std::istream& input, Number number) {
    static_assert(std::is_integral_v<Number>, "Number not integral");
    string line;
    std::vector<Domain> result;
    result.reserve(number);
    for (Number i = 0; i < number; ++i) {
        getline(input, line);
        result.emplace_back(line);
    }
    return result;
}

void Process(std::istream& in, std::ostream& out) {
    const std::vector<Domain> forbidden_domains = ReadDomains(in, ReadNumberOnLine<size_t>(in));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(in, ReadNumberOnLine<size_t>(in));
    for (const Domain& domain : test_domains) {
        out << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}

void CheckYandexExample() {
    std::istringstream in("4\n"
                          "gdz.ru\n"
                          "maps.me\n"
                          "m.gdz.ru\n"
                          "com\n"
                          "7\n"
                          "gdz.ru\n"
                          "gdz.com\n"
                          "m.maps.me\n"
                          "alg.m.gdz.ru\n"
                          "maps.com\n"
                          "maps.ru\n"
                          "gdz.ua\n");
    std::ostringstream right_out("Bad\n"
                                 "Bad\n"
                                 "Bad\n"
                                 "Bad\n"
                                 "Bad\n"
                                 "Good\n"
                                 "Good\n");
    std::ostringstream out;
    Process(in, out);
    std::cout << out.str();
    assert(out.str() == right_out.str() && "NOT OK");
    std::cerr << "OK\n";

}

void Main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}

int main() {
    Main();
//    CheckYandexExample();
}