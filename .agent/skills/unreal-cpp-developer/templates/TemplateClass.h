// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TEMPLATE_CLASS_NAME.generated.h"

/**
 * UTEMPLATE_CLASS_NAME
 *
 * <Description of what this class does>
 */
UCLASS(BlueprintType, Blueprintable)
    class YOURMODULE_API UTEMPLATE_CLASS_NAME : public UObject
    {
        GENERATED_BODY()

    public:
        UTEMPLATE_CLASS_NAME();

        /**
         * <Description of the function>
         *
         * @param ParamName <Description of parameter>
         * @return <Description of return value>
         */
        UFUNCTION(BlueprintCallable, Category = "YourCategory|YourSubCategory")
        void ExampleFunction(int ParamName);

    protected:
        /** <Description of the property> */
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YourCategory|YourSubCategory")
        int ExampleProperty;
    };
