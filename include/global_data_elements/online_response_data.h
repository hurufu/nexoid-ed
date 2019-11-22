#pragma once

struct OnlineResponseData {
    enum AuthorisationResponseCode authorisationResponseCode;
    char declineDisplayMessage[40 + 1];
};
