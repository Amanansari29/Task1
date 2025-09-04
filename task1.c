#include <stdio.h>

// Simple Linear Regression (3 features)
void linearRegression(double X[][3], double Y[], int n, double coeffs[4]) {
    double sumX1 = 0, sumX2 = 0, sumX3 = 0, sumY = 0;
    double sumX1Y = 0, sumX2Y = 0, sumX3Y = 0;
    double sumX1X1 = 0, sumX2X2 = 0, sumX3X3 = 0;

    for (int i = 0; i < n; i++) {
        double x1 = X[i][0]; // sqft
        double x2 = X[i][1]; // bedrooms
        double x3 = X[i][2]; // bathrooms
        double y  = Y[i];

        sumX1 += x1;
        sumX2 += x2;
        sumX3 += x3;
        sumY  += y;

        sumX1Y += x1 * y;
        sumX2Y += x2 * y;
        sumX3Y += x3 * y;

        sumX1X1 += x1 * x1;
        sumX2X2 += x2 * x2;
        sumX3X3 += x3 * x3;
    }

    coeffs[1] = sumX1Y / sumX1X1;  // sqft weight
    coeffs[2] = sumX2Y / sumX2X2;  // bedrooms weight
    coeffs[3] = sumX3Y / sumX3X3;  // bathrooms weight
    coeffs[0] = (sumY - coeffs[1] * sumX1 - coeffs[2] * sumX2 - coeffs[3] * sumX3) / n;
}

int main() {
    int n;
    printf("Enter number of houses in dataset: ");
    scanf("%d", &n);

    double X[n][3], Y[n];

    // Input dataset
    for (int i = 0; i < n; i++) {
        printf("\nHouse %d:\n", i + 1);
        printf("Enter square feet: ");
        scanf("%lf", &X[i][0]);
        printf("Enter number of bedrooms: ");
        scanf("%lf", &X[i][1]);
        printf("Enter number of bathrooms: ");
        scanf("%lf", &X[i][2]);
        printf("Enter price: ");
        scanf("%lf", &Y[i]);
    }

    double coeffs[4];
    linearRegression(X, Y, n, coeffs);

    printf("\nModel trained successfully!\n");
    printf("Price = %.2f + %.2f*(sqft) + %.2f*(bedrooms) + %.2f*(bathrooms)\n",
           coeffs[0], coeffs[1], coeffs[2], coeffs[3]);

    // Predictions for all dataset houses
    printf("\nPredicted Prices for all dataset houses:\n");
    for (int i = 0; i < n; i++) {
        double predicted = coeffs[0] + coeffs[1] * X[i][0] + coeffs[2] * X[i][1] + coeffs[3] * X[i][2];
        printf("House %d → Actual: %.2f | Predicted: %.2f\n", i + 1, Y[i], predicted);
    }

    // Prediction for new house
    double sqft, bedrooms, bathrooms;
    printf("\nEnter details of a new house to predict price:\n");
    printf("Square feet: ");
    scanf("%lf", &sqft);
    printf("Bedrooms: ");
    scanf("%lf", &bedrooms);
    printf("Bathrooms: ");
    scanf("%lf", &bathrooms);

    double predicted = coeffs[0] + coeffs[1] * sqft + coeffs[2] * bedrooms + coeffs[3] * bathrooms;
    printf("\nPredicted Price for new house = %.2f\n", predicted);

    return 0;
}