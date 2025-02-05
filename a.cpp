#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Product {
    string name;
    double price;
    int quantity;
};

vector<Product> productList;
vector<Product> cart;

// Merge two subarrays sorted by name
void mergeByName(vector<Product>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    vector<Product> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].name <= rightArr[j].name)
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

// Merge two subarrays sorted by price
void mergeByPrice(vector<Product>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    vector<Product> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].price <= rightArr[j].price)
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

// Merge Sort function
void mergeSort(vector<Product>& arr, int left, int right, bool sortByPrice) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, sortByPrice);
        mergeSort(arr, mid + 1, right, sortByPrice);
        if (sortByPrice)
            mergeByPrice(arr, left, mid, right);
        else
            mergeByName(arr, left, mid, right);
    }
}

// Binary search for product by name
int binarySearch(const vector<Product>& arr, const string& name) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].name == name)
            return mid;
        else if (arr[mid].name < name)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Function to search product
void searchProduct() {
    string name;
    cout << "Enter product name to search: ";
    cin >> name;
    mergeSort(productList, 0, productList.size() - 1, false); // Sort by name
    int index = binarySearch(productList, name);
    if (index != -1) {
        cout << "Product found:\n";
        cout << "Name: " << productList[index].name << ", Price: $" << fixed << setprecision(2) << productList[index].price
             << ", Quantity: " << productList[index].quantity << endl;
    } else {
        cout << "Product not found!\n";
    }
}

// Function to view products
void viewProducts() {
    if (productList.empty()) {
        cout << "No products available.\n";
        return;
    }
    cout << "\nAvailable Products:\n";
    for (const auto& p : productList) {
        cout << "Name: " << p.name << ", Price: $" << fixed << setprecision(2) << p.price
             << ", Quantity: " << p.quantity << endl;
    }
}

// Function to add a new product (Admin)
void addProduct() {
    Product newProduct;
    cout << "Enter product name: ";
    cin >> newProduct.name;
    cout << "Enter price: ";
    cin >> newProduct.price;
    cout << "Enter quantity: ";
    cin >> newProduct.quantity;
    productList.push_back(newProduct);
    cout << "Product added successfully!\n";
}

// Function to update an existing product (Admin)
void updateProduct() {
    string name;
    cout << "Enter product name to update: ";
    cin >> name;
    for (auto& p : productList) {
        if (p.name == name) {
            cout << "Enter new price: ";
            cin >> p.price;
            cout << "Enter new quantity: ";
            cin >> p.quantity;
            cout << "Product updated successfully!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}

// Function to delete a product (Admin)
void deleteProduct() {
    string name;
    cout << "Enter product name to delete: ";
    cin >> name;
    for (auto it = productList.begin(); it != productList.end(); ++it) {
        if (it->name == name) {
            productList.erase(it);
            cout << "Product deleted successfully!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}

// Function to purchase a product (Customer & Admin)
void purchaseProduct() {
    string name;
    int quantity;
    cout << "Enter product to purchase: ";
    cin >> name;
    cout << "Enter quantity: ";
    cin >> quantity;
    for (auto& p : productList) {
        if (p.name == name && p.quantity >= quantity) {
            double totalCost = p.price * quantity;
            p.quantity -= quantity;
            cart.push_back({name, p.price, quantity});
            cout << "Purchased " << quantity << " of " << p.name << " for $" << fixed << setprecision(2) << totalCost << endl;
            cout << "Remaining quantity: " << p.quantity << endl;
            return;
        }
    }
    cout << "Product not available or insufficient quantity!\n";
}

// Function to generate receipt (Customer & Admin)
void generateReceipt() {
    if (cart.empty()) {
        cout << "Cart is empty.\n";
        return;
    }
    double grandTotal = 0;
    cout << "\nReceipt:\n";
    for (const auto& item : cart) {
        double itemTotal = item.price * item.quantity;
        cout << item.name << " " << item.quantity << " x $" << fixed << setprecision(2) << item.price << " = $" << itemTotal << endl;
        grandTotal += itemTotal;
    }
    cout << "Grand Total: $" << fixed << setprecision(2) << grandTotal << endl;
}

// Function to view sorted products
void viewSortedProducts() {
    if (productList.empty()) {
        cout << "No products available.\n";
        return;
    }
    int sortChoice;
    cout << "1. Sort by Name\n2. Sort by Price\nEnter choice: ";
    cin >> sortChoice;
    bool sortByPrice = (sortChoice == 2);
    mergeSort(productList, 0, productList.size() - 1, sortByPrice);
    cout << "\nSorted Products:\n";
    viewProducts();
}

// Authentication and role selection
int main() {
    while (true) {
        int roleChoice;
        cout << "1. Log in as Admin\n2. Log in as Customer\nEnter choice: ";
        cin >> roleChoice;
        if (roleChoice == 1) {
            string user, pass;
            cout << "Enter Admin Username: ";
            cin >> user;
            cout << "Enter Admin Password: ";
            cin >> pass;
            if (user == "admin" && pass == "admin") {
                cout << "Admin Login Successful!\n";
                while (true) {
                    cout << "\n1. View Products\n2. View Sorted Products\n3. Search Product\n4. Add Product\n5. Update Product\n6. Delete Product\n7. Purchase Product\n8. Generate Receipt\n9. Log Out\n";
                    cout << "Enter your choice: ";
                    int choice;
                    cin >> choice;
                    if (choice == 1) viewProducts();
                    else if (choice == 2) viewSortedProducts();
                    else if (choice == 3) searchProduct();
                    else if (choice == 4) addProduct();
                    else if (choice == 5) updateProduct();
                    else if (choice == 6) deleteProduct();
                    else if (choice == 7) purchaseProduct();
                    else if (choice == 8) generateReceipt();
                    else if (choice == 9) break; // Log out
                    else cout << "Invalid choice!\n";
                }
            } else {
                cout << "Invalid credentials!\n";
            }
        } else if (roleChoice == 2) {
            cout << "Customer Login Successful!\n";
            while (true) {
                cout << "\n1. View Products\n2. View Sorted Products\n3. Search Product\n4. Purchase Product\n5. Generate Receipt\n6. Log Out\n";
                cout << "Enter your choice: ";
                int choice;
                cin >> choice;
                if (choice == 1) viewProducts();
                else if (choice == 2) viewSortedProducts();
                else if (choice == 3) searchProduct();
                else if (choice == 4) purchaseProduct();
                else if (choice == 5) generateReceipt();
                else if (choice == 6) break; // Log out
                else cout << "Invalid choice!\n";
            }
        } else {
            cout << "Invalid choice! Please choose a valid role.\n";
        }
    }
    return 0;
}