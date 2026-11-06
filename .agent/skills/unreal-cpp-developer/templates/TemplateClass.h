#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TEMPLATE_CLASS_NAME.generated.h"

// Replace the class name, module API macro, category, and example members.
// This is a UObject example; choose the appropriate base and lifecycle for the requested class.
// Keep these instructions in the template, but omit them from generated project code.
UCLASS(BlueprintType, Blueprintable)
class YOURMODULE_API UTEMPLATE_CLASS_NAME : public UObject
{
    GENERATED_BODY()

public:
    UTEMPLATE_CLASS_NAME();

    /**
     * Sets the example value.
     * @param InValue The new value to store.
     */
    UFUNCTION(BlueprintCallable, Category = "YourCategory|YourSubCategory")
    void ExampleFunction(int32 InValue);

protected:
    /** The current example value. Replace this tooltip with the property's meaning and units. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YourCategory|YourSubCategory")
    int32 ExampleProperty;
};
