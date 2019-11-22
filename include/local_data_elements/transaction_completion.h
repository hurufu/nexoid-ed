#pragma once

enum DeliveryResult {
    DELIVERY_OK,
    DELIVERY_NOK,
    DELIVERY_PARTIAL
};

struct TransactionCompletion {
    bool printCardholderReceipt;
    bool printMerchantReceipt;
    enum DeliveryResult deliveryResult;
    union Amount reducedAmount;
};
